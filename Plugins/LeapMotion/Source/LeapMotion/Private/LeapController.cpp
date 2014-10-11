#include "LeapMotionPrivatePCH.h"
#include "Engine.h"
#include "CoreUObject.h"
#include "Slate.h"

#define LOCTEXT_NAMESPACE "LeapPlugin"

//Input Mapping Keys
//todo: input mapping left for another day
/*struct EKeysLeap
{
	//Left Hand Actions
	static const FKey LeapLeftPinch;
	static const FKey LeapLeftGrab;
	static const FKey LeapLeftFingerTouch;

	//Left Hand Rotations
	static const FKey LeapLeftPalmRotation;

	//Right Hand Actions
	static const FKey LeapRightPinch;
	static const FKey LeapRightGrab;
	static const FKey LeapRightFingerTouch;

	//Right Hand Rotations
	static const FKey LeapRightPalmRotation;
};

//FKey declarations
//Define each FKey const in a .cpp so we can compile
const FKey EKeysLeap::LeapLeftPinch("LeapLeftPinch");
const FKey EKeysLeap::LeapLeftGrab("LeapLeftGrab");
const FKey EKeysLeap::LeapLeftFingerTouch("LeapLeftFingerTouch");
const FKey EKeysLeap::LeapLeftPalmRotation("LeapLeftPalmRotation");
const FKey EKeysLeap::LeapRightPinch("LeapRightPinch");
const FKey EKeysLeap::LeapRightGrab("LeapRightGrab");
const FKey EKeysLeap::LeapRightFingerTouch("LeapRightFingerTouch");
const FKey EKeysLeap::LeapRightPalmPitch("LeapRightPalmPitch");
const FKey EKeysLeap::LeapRightPalmYaw("LeapRightPalmYaw");
const FKey EKeysLeap::LeapRightPalmRotation("LeapRightPalmRotation");*/

//LeapStateData
bool LeapStateData::hasStateForId(int32 hId, LeapHandStateData& state)
{
	for (size_t i = 0; i < handStates.size(); ++i) {
		// If two Myo pointers compare equal, they refer to the same Myo device.
		if (handStates[i].id == hId) {
			state = handStates[i];
			return true;
		}
	}
	return false;
}

LeapHandStateData LeapStateData::stateForId(int32 hId)
{
	LeapHandStateData handState;
	if (!hasStateForId(hId, handState)){
		handState.id = hId;
		handStates.push_back(handState);
	}

	return handState;
}

void LeapStateData::setStateForId(LeapHandStateData handState, int32 hId)
{
	for (size_t i = 0; i < handStates.size(); ++i) {
		// If two Myo pointers compare equal, they refer to the same Myo device.
		if (handStates[i].id == hId) {
			handStates[i] = handState;
		}
	}
}


ULeapController::ULeapController(const FPostConstructInitializeProperties &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to

	//Attach Input Mapping
	//EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftGrab, LOCTEXT("LeapLeftGrab", "Leap Left Grab"), FKeyDetails::GamepadKey));
}

ULeapController::~ULeapController()
{
}

bool ULeapController::isConnected() const
{
	return _leap.isConnected();
}

void ULeapController::InitializeComponent()
{
	Super::InitializeComponent();
}

void ULeapController::TickComponent(float DeltaTime, enum ELevelTick TickType,
									FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Forward the component tick
	InterfaceEventTick(DeltaTime);
}

void ULeapController::BeginDestroy()
{
	Super::BeginDestroy();
}

const Leap::Controller &ULeapController::getData() const
{
	return (_leap);
}

ULeapFrame *ULeapController::getFrame(int32 history)
{
	ULeapFrame *rframe;


	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_leap, history);
	return (rframe);
}

bool ULeapController::hasFocus() const
{
	return (_leap.hasFocus());
}

bool ULeapController::isServiceConnected() const
{
	return (_leap.isServiceConnected());
}

void ULeapController::optimizeForHMD(bool useTopdown) const
{
	if (useTopdown)
		_leap.setPolicyFlags(Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);
	else
		_leap.setPolicyFlags(Leap::Controller::PolicyFlag::POLICY_DEFAULT);
}

//Leap Event Interface - Event Driven System

void ULeapController::SetInterfaceDelegate(UObject* newDelegate)
{
	//Use this format to support both blueprint and C++ form
	if (newDelegate->GetClass()->ImplementsInterface(ULeapEventInterface::StaticClass()))
	{
		_interfaceDelegate = newDelegate;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("LeapController Warning: Delegate is NOT set, did you implement LeapEventInterface?"));
	}
}


//Utility
bool handClosed(float strength)
{
	return (strength == 1.f);
}

bool handForId(int32 checkId, Leap::HandList hands, Leap::Hand& returnHand)
{
	for (int i = 0; i < hands.count(); i++)
	{
		Leap::Hand hand = hands[i];
		if (checkId == hand.id()){
			returnHand = hand;
			return true;
		}
	}
	return false;
}

//Main Event driven tick
void ULeapController::InterfaceEventTick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Tick1!"));

	//This is our tick event that is forwarded from the delegate
	if (!_interfaceDelegate) return;

	//Pointers
	Leap::Frame frame = _leap.frame();
	Leap::Frame pastFrame = _leap.frame(1);

	//-Hands-

	//Hand Count
	int handCount = frame.hands().count();

	if (_pastState.handCount != handCount)
		ILeapEventInterface::Execute_LeapHandsDetected(_interfaceDelegate, handCount);

	//Cycle through each hand
	for (int i = 0; i < handCount; i++)
	{
		Leap::Hand hand = frame.hands()[i];
		LeapHandStateData pastHandState = _pastState.stateForId(hand.id());		//we use a custom class to hold reliable state tracking based on id's

		//Make a UHand
		UHand *uHand = ConstructObject<UHand>(UHand::StaticClass());
		uHand->setHand(hand);

		//Emit hand
		ILeapEventInterface::Execute_LeapHandMoved(_interfaceDelegate, uHand);

		//Left/Right hand forwarding
		if (hand.isRight())
			ILeapEventInterface::Execute_LeapRightHandMoved(_interfaceDelegate, uHand);
		else if (hand.isLeft())
			ILeapEventInterface::Execute_LeapLeftHandMoved(_interfaceDelegate, uHand);

		//Grabbing
		float grabStrength = hand.grabStrength();
		bool grabbed = handClosed(grabStrength);

		if (grabbed && !pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandGrabbed(_interfaceDelegate, grabStrength, uHand);
		else if (!grabbed && pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandReleased(_interfaceDelegate, grabStrength, uHand);

		//Pinching
		float pinchStrength = hand.pinchStrength();
		bool pinched = handClosed(pinchStrength);

		if (pinched && !pastHandState.pinched)
			ILeapEventInterface::Execute_LeapHandPinched(_interfaceDelegate, pinchStrength, uHand);
		else if (!pinched && pastHandState.pinched)
			ILeapEventInterface::Execute_LeapHandUnpinched(_interfaceDelegate, pinchStrength, uHand);

		//-Fingers-
		Leap::FingerList fingers = hand.fingers();

		//Count
		int fingerCount = fingers.count();
		if ((pastHandState.fingerCount != fingerCount))
			ILeapEventInterface::Execute_LeapFingersDetected(_interfaceDelegate, fingerCount);

		UFinger *uFinger = ConstructObject<UFinger>(UFinger::StaticClass());
		Leap::Finger finger;

		//Cycle through each finger
		for (int j = 0; j < fingerCount; j++)
		{
			finger = fingers[j];
			uFinger->setFinger(finger);

			//Finger Moved
			ILeapEventInterface::Execute_LeapFingerMoved(_interfaceDelegate, uFinger);
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		finger = fingers.leftmost();
		uFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapLeftMostFingerMoved(_interfaceDelegate, uFinger);

		//Rightmost
		finger = fingers.rightmost();
		uFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapRightMostFingerMoved(_interfaceDelegate, uFinger);

		//Frontmost
		finger = fingers.frontmost();
		uFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapFrontMostFingerMoved(_interfaceDelegate, uFinger);

		//touch only for front most finger
		float touchDistance = finger.touchDistance();
		if (touchDistance <= 0)
			ILeapEventInterface::Execute_LeapFingerTouch(_interfaceDelegate, uFinger);

		//Set the state data for next cycle
		pastHandState.grabbed = grabbed;
		pastHandState.pinched = pinched;
		pastHandState.fingerCount = fingerCount;

		_pastState.setStateForId(pastHandState, hand.id());
	}

	_pastState.handCount = handCount;
}

#undef LOCTEXT_NAMESPACE
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

	//Attach Input Mapping - left for another day
	//e.g. EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftGrab, LOCTEXT("LeapLeftGrab", "Leap Left Grab"), FKeyDetails::GamepadKey));
}

ULeapController::~ULeapController()
{
}

bool ULeapController::isConnected() const
{
	return _leap.isConnected();
}

void ULeapController::OnRegister()
{
	Super::OnRegister();

	//Attach the delegate pointer automatically
	SetInterfaceDelegate(GetOwner());
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
	if (!_frame)
		_frame = NewObject<ULeapFrame>(this, ULeapFrame::StaticClass());
	_frame->setFrame(_leap, history);
	return (_frame);
}

bool ULeapController::hasFocus() const
{
	return (_leap.hasFocus());
}

bool ULeapController::isServiceConnected() const
{
	return (_leap.isServiceConnected());
}

Leap::Controller::PolicyFlag ULeapController::buildPolicyFromBools(){
	Leap::Controller::PolicyFlag policies = Leap::Controller::PolicyFlag::POLICY_DEFAULT;

	if (_optimizeForHMD)
		policies = static_cast<Leap::Controller::PolicyFlag>(policies | Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);
	if (_allowImages)
		policies = static_cast<Leap::Controller::PolicyFlag>(policies | Leap::Controller::PolicyFlag::POLICY_IMAGES);
	return policies;
}

void ULeapController::optimizeForHMD(bool useTopdown, bool autoRotate, bool autoShift)
{
	//Set Policy Optimization
	_optimizeForHMD = useTopdown;
	_leap.setPolicyFlags(buildPolicyFromBools());

	//Pass adjustment booleans
	if (useTopdown)
		LeapSetShouldAdjustForFacing(true);
	else
		LeapSetShouldAdjustForFacing(false);

	LeapSetShouldAdjustForHMD(autoRotate, autoShift);
}

void ULeapController::enableImageSupport(bool allowImages)
{
	_allowImages = allowImages;
	_leap.setPolicyFlags(buildPolicyFromBools());
}

void ULeapController::enableGesture(LeapGestureType type, bool enable)
{
	Leap::Gesture::Type rawType;

	switch (type)
	{
	case GESTURE_TYPE_CIRCLE:
		rawType = Leap::Gesture::TYPE_CIRCLE;
		break;
	case GESTURE_TYPE_KEY_TAP:
		rawType = Leap::Gesture::TYPE_KEY_TAP;
		break;
	case GESTURE_TYPE_SCREEN_TAP:
		rawType = Leap::Gesture::TYPE_SCREEN_TAP;
		break;
	case GESTURE_TYPE_SWIPE:
		rawType = Leap::Gesture::TYPE_SWIPE;
		break;
	default:
		rawType = Leap::Gesture::TYPE_INVALID;
		break;
	}

	_leap.enableGesture(rawType, enable);
}

//Leap Event Interface - Event Driven System
void ULeapController::SetInterfaceDelegate(UObject* newDelegate)
{

	UE_LOG(LogClass, Log, TEXT("InterfaceObject: %s"), *newDelegate->GetName());

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

bool handPinched(float strength)
{
	return (strength > 0.8);
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
	//This is our tick event that is forwarded from the delegate, check validity
	if (!_interfaceDelegate) return;

	//Pointers
	Leap::Frame frame = _leap.frame();
	Leap::Frame pastFrame = _leap.frame(1);

	//-Hands-

	//Hand Count
	int handCount = frame.hands().count();

	if (_pastState.handCount != handCount)
		ILeapEventInterface::Execute_HandCountChanged(_interfaceDelegate, handCount);

	//Cycle through each hand
	for (int i = 0; i < handCount; i++)
	{
		Leap::Hand hand = frame.hands()[i];
		LeapHandStateData pastHandState = _pastState.stateForId(hand.id());		//we use a custom class to hold reliable state tracking based on id's

		//Make a UHand
		if (!_eventHand)
			_eventHand = NewObject<UHand>(this);
		_eventHand->setHand(hand);

		//Emit hand
		ILeapEventInterface::Execute_LeapHandMoved(_interfaceDelegate, _eventHand);

		//Left/Right hand forwarding
		if (hand.isRight())
			ILeapEventInterface::Execute_LeapRightHandMoved(_interfaceDelegate, _eventHand);
		else if (hand.isLeft())
			ILeapEventInterface::Execute_LeapLeftHandMoved(_interfaceDelegate, _eventHand);

		//Grabbing
		float grabStrength = hand.grabStrength();
		bool grabbed = handClosed(grabStrength);

		if (grabbed)
			ILeapEventInterface::Execute_LeapHandGrabbing(_interfaceDelegate, grabStrength, _eventHand);

		if (grabbed && !pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandGrabbed(_interfaceDelegate, grabStrength, _eventHand);
		else if (!grabbed && pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandReleased(_interfaceDelegate, grabStrength, _eventHand);

		//Pinching
		float pinchStrength = hand.pinchStrength();
		bool pinched = handPinched(pinchStrength);

		//While grabbing disable pinching detection, this helps to reduce spam as pose confidence plummets
		if (grabbed) pinched = pastHandState.pinched;
		else
		{
			if (pinched)
				ILeapEventInterface::Execute_LeapHandPinching(_interfaceDelegate, pinchStrength, _eventHand);

			if (pinched && !pastHandState.pinched)
				ILeapEventInterface::Execute_LeapHandPinched(_interfaceDelegate, pinchStrength, _eventHand);
			else if (!pinched && pastHandState.pinched)
				ILeapEventInterface::Execute_LeapHandUnpinched(_interfaceDelegate, pinchStrength, _eventHand);
		}

		//-Fingers-
		Leap::FingerList fingers = hand.fingers();

		//Count
		int fingerCount = fingers.count();
		if ((pastHandState.fingerCount != fingerCount))
			ILeapEventInterface::Execute_FingerCountChanged(_interfaceDelegate, fingerCount);

		if (!_eventFinger)
			_eventFinger = NewObject<UFinger>(this);

		Leap::Finger finger;

		//Cycle through each finger
		for (int j = 0; j < fingerCount; j++)
		{
			finger = fingers[j];
			_eventFinger->setFinger(finger);

			//Finger Moved
			ILeapEventInterface::Execute_LeapFingerMoved(_interfaceDelegate, _eventFinger);
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		finger = fingers.leftmost();
		_eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapLeftMostFingerMoved(_interfaceDelegate, _eventFinger);

		//Rightmost
		finger = fingers.rightmost();
		_eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapRightMostFingerMoved(_interfaceDelegate, _eventFinger);

		//Frontmost
		finger = fingers.frontmost();
		_eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapFrontMostFingerMoved(_interfaceDelegate, _eventFinger);

		//touch only for front-most finger, most common use case
		float touchDistance = finger.touchDistance();
		if (touchDistance <= 0.f)
			ILeapEventInterface::Execute_LeapFrontFingerTouch(_interfaceDelegate, _eventFinger);

		//Set the state data for next cycle
		pastHandState.grabbed = grabbed;
		pastHandState.pinched = pinched;
		pastHandState.fingerCount = fingerCount;

		_pastState.setStateForId(pastHandState, hand.id());
	}

	_pastState.handCount = handCount;

	//Gestures
	for (int i = 0; i < frame.gestures().count(); i++)
	{
		Leap::Gesture gesture = frame.gestures()[i];

		//emit gesture
		if (gesture.type() != Leap::Gesture::TYPE_INVALID)
		{
			if (!_eventGesture)
				_eventGesture = NewObject<UGesture>(this);
			_eventGesture->setGesture(gesture);
			ILeapEventInterface::Execute_GestureDetected(_interfaceDelegate, _eventGesture);
		}
	}
}

#undef LOCTEXT_NAMESPACE
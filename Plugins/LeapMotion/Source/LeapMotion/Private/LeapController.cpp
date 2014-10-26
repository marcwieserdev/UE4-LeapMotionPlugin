#include "LeapMotionPrivatePCH.h"
#include "Slate.h"
#include <vector>

#include <sstream> //for std::stringstream 
#include <string>  //for std::string

#include "ILeapMotion.h"

#define LOCTEXT_NAMESPACE "LeapPlugin"

//Utility function used to debug address allocation - helped find the cdcdcdcd error
void debugAddress(void* pointer)
{
	const void * address = static_cast<const void*>(pointer);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	FString string(name.c_str());

	UE_LOG(LogTemp, Warning, TEXT("Address: %s"), *string);
}

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

//Used for Reliable State Tracking
struct LeapHandStateData{
	bool grabbed;
	bool pinched;
	int32 fingerCount;
	int32 id;
};

class LeapStateData{
public:
	bool hasStateForId(int32 hId, LeapHandStateData& state);
	LeapHandStateData stateForId(int32 hId);
	void setStateForId(LeapHandStateData handState, int32 hId);

	std::vector<LeapHandStateData> handStates;
	int32 handCount;
};

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

class LeapControllerPrivate
{
public:
	//Properties and Pointers
	LeapStateData pastState;
	Leap::Controller leap;
	ULeapFrame* frame = NULL;
	UHand* eventHand = NULL;
	UFinger* eventFinger = NULL;
	UGesture* eventGesture = NULL;
	UCircleGesture* eventCircleGesture = NULL;
	UKeyTapGesture* eventKeyTapGesture = NULL;
	UScreenTapGesture* eventScreenTapGesture = NULL;
	USwipeGesture* eventSwipeGesture = NULL;
	
	UObject* interfaceDelegate = NULL;	//NB they have to be set to null manually or MSFT will set them to CDCDCDCD...
	bool optimizeForHMD;
	bool allowImages;

	//Functions
	Leap::Controller::PolicyFlag buildPolicyFromBools();
	void SetPolicyFlagsFromBools();

};

//LeapControllerPrivate
Leap::Controller::PolicyFlag LeapControllerPrivate::buildPolicyFromBools(){
	Leap::Controller::PolicyFlag policies = Leap::Controller::PolicyFlag::POLICY_DEFAULT;

	if (optimizeForHMD)
		policies = static_cast<Leap::Controller::PolicyFlag>(policies | Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD);
	if (allowImages)
		policies = static_cast<Leap::Controller::PolicyFlag>(policies | Leap::Controller::PolicyFlag::POLICY_IMAGES);
	return policies;
}

void LeapControllerPrivate::SetPolicyFlagsFromBools()
{
	leap.setPolicyFlags(buildPolicyFromBools());
}

//ULeapController
ULeapController::ULeapController(const FPostConstructInitializeProperties &init) : UActorComponent(init), _private(new LeapControllerPrivate())
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to

	//Attach Input Mapping - left for another day
	//e.g. EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftGrab, LOCTEXT("LeapLeftGrab", "Leap Left Grab"), FKeyDetails::GamepadKey));
	//_private->leap = new Leap::Controller();
}

ULeapController::~ULeapController()
{
	delete _private;
}

bool ULeapController::isConnected() const
{
	return _private->leap.isConnected();
}

void ULeapController::OnRegister()
{
	Super::OnRegister();

	/*if (ILeapMotion::IsAvailable())
	{
		_private->leap = ILeapMotion::Get().Controller();
	}*/

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

ULeapFrame* ULeapController::Frame(int32 history)
{
	if (_private->frame == NULL)
		_private->frame = NewObject<ULeapFrame>(this, ULeapFrame::StaticClass());
	_private->frame->setFrame(_private->leap, history);
	return (_private->frame);
}

bool ULeapController::hasFocus() const
{
	return (_private->leap.hasFocus());
}

bool ULeapController::isServiceConnected() const
{
	return (_private->leap.isServiceConnected());
}


void ULeapController::optimizeForHMD(bool useTopdown, bool autoRotate, bool autoShift)
{
	//Set Policy Optimization
	_private->optimizeForHMD = useTopdown;
	_private->SetPolicyFlagsFromBools();

	//Pass adjustment booleans
	if (useTopdown)
		LeapSetShouldAdjustForFacing(true);
	else
		LeapSetShouldAdjustForFacing(false);

	LeapSetShouldAdjustForHMD(autoRotate, autoShift);
}

void ULeapController::enableImageSupport(bool allowImages)
{
	_private->allowImages = allowImages;
	_private->SetPolicyFlagsFromBools();
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

	_private->leap.enableGesture(rawType, enable);
}

//Leap Event Interface - Event Driven System
void ULeapController::SetInterfaceDelegate(UObject* newDelegate)
{

	UE_LOG(LogClass, Log, TEXT("InterfaceObject: %s"), *newDelegate->GetName());

	//Use this format to support both blueprint and C++ form
	if (newDelegate->GetClass()->ImplementsInterface(ULeapEventInterface::StaticClass()))
	{
		_private->interfaceDelegate = newDelegate;
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
	if (!_private->interfaceDelegate) return;

	//Pointers
	Leap::Frame frame = _private->leap.frame();
	Leap::Frame pastFrame = _private->leap.frame(1);

	//-Hands-

	//Hand Count
	int handCount = frame.hands().count();

	if (_private->pastState.handCount != handCount)
		ILeapEventInterface::Execute_HandCountChanged(_private->interfaceDelegate, handCount);

	//Cycle through each hand
	for (int i = 0; i < handCount; i++)
	{
		Leap::Hand hand = frame.hands()[i];
		LeapHandStateData pastHandState = _private->pastState.stateForId(hand.id());		//we use a custom class to hold reliable state tracking based on id's

		/*UE_LOG(LogTemp, Warning, TEXT("Debug1"));

		debugAddress(this);
		debugAddress(this->_private);
		debugAddress(this->_private->eventHand);
		debugAddress(NULL);*/

		//Make a UHand
		if (_private->eventHand == NULL)
			_private->eventHand = NewObject<UHand>(this);

		_private->eventHand->setHand(hand);

		//Emit hand
		ILeapEventInterface::Execute_LeapHandMoved(_private->interfaceDelegate, _private->eventHand);

		//Left/Right hand forwarding
		if (hand.isRight())
			ILeapEventInterface::Execute_LeapRightHandMoved(_private->interfaceDelegate, _private->eventHand);
		else if (hand.isLeft())
			ILeapEventInterface::Execute_LeapLeftHandMoved(_private->interfaceDelegate, _private->eventHand);

		//Grabbing
		float grabStrength = hand.grabStrength();
		bool grabbed = handClosed(grabStrength);

		if (grabbed)
			ILeapEventInterface::Execute_LeapHandGrabbing(_private->interfaceDelegate, grabStrength, _private->eventHand);

		if (grabbed && !pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandGrabbed(_private->interfaceDelegate, grabStrength, _private->eventHand);
		else if (!grabbed && pastHandState.grabbed)
			ILeapEventInterface::Execute_LeapHandReleased(_private->interfaceDelegate, grabStrength, _private->eventHand);

		//Pinching
		float pinchStrength = hand.pinchStrength();
		bool pinched = handPinched(pinchStrength);

		//While grabbing disable pinching detection, this helps to reduce spam as pose confidence plummets
		if (grabbed) pinched = pastHandState.pinched;
		else
		{
			if (pinched)
				ILeapEventInterface::Execute_LeapHandPinching(_private->interfaceDelegate, pinchStrength, _private->eventHand);

			if (pinched && !pastHandState.pinched)
				ILeapEventInterface::Execute_LeapHandPinched(_private->interfaceDelegate, pinchStrength, _private->eventHand);
			else if (!pinched && pastHandState.pinched)
				ILeapEventInterface::Execute_LeapHandUnpinched(_private->interfaceDelegate, pinchStrength, _private->eventHand);
		}

		//-Fingers-
		Leap::FingerList fingers = hand.fingers();

		//Count
		int fingerCount = fingers.count();
		if ((pastHandState.fingerCount != fingerCount))
			ILeapEventInterface::Execute_FingerCountChanged(_private->interfaceDelegate, fingerCount);

		if (_private->eventFinger == NULL)
			_private->eventFinger = NewObject<UFinger>(this);

		Leap::Finger finger;

		//Cycle through each finger
		for (int j = 0; j < fingerCount; j++)
		{
			finger = fingers[j];
			_private->eventFinger->setFinger(finger);

			//Finger Moved
			if (finger.isValid())
				ILeapEventInterface::Execute_LeapFingerMoved(_private->interfaceDelegate, _private->eventFinger);
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		finger = fingers.leftmost();
		_private->eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapLeftMostFingerMoved(_private->interfaceDelegate, _private->eventFinger);

		//Rightmost
		finger = fingers.rightmost();
		_private->eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapRightMostFingerMoved(_private->interfaceDelegate, _private->eventFinger);

		//Frontmost
		finger = fingers.frontmost();
		_private->eventFinger->setFinger(finger);
		ILeapEventInterface::Execute_LeapFrontMostFingerMoved(_private->interfaceDelegate, _private->eventFinger);

		//touch only for front-most finger, most common use case
		float touchDistance = finger.touchDistance();
		if (touchDistance <= 0.f)
			ILeapEventInterface::Execute_LeapFrontFingerTouch(_private->interfaceDelegate, _private->eventFinger);

		//Set the state data for next cycle
		pastHandState.grabbed = grabbed;
		pastHandState.pinched = pinched;
		pastHandState.fingerCount = fingerCount;

		_private->pastState.setStateForId(pastHandState, hand.id());
	}

	_private->pastState.handCount = handCount;

	//Gestures
	for (int i = 0; i < frame.gestures().count(); i++)
	{
		Leap::Gesture gesture = frame.gestures()[i];
		Leap::Gesture::Type type = gesture.type();

		switch (type)
		{
		case Leap::Gesture::TYPE_CIRCLE:
			if (_private->eventCircleGesture == NULL)
				_private->eventCircleGesture = NewObject<UCircleGesture>(this);
			_private->eventCircleGesture->setGesture(Leap::CircleGesture(gesture));
			ILeapEventInterface::Execute_CircleGestureDetected(_private->interfaceDelegate, _private->eventCircleGesture);
			_private->eventGesture = _private->eventCircleGesture;
			break;
		case Leap::Gesture::TYPE_KEY_TAP:
			if (_private->eventKeyTapGesture == NULL)
				_private->eventKeyTapGesture = NewObject<UKeyTapGesture>(this);
			_private->eventKeyTapGesture->setGesture(Leap::KeyTapGesture(gesture));
			ILeapEventInterface::Execute_KeyTapGestureDetected(_private->interfaceDelegate, _private->eventKeyTapGesture);
			_private->eventGesture = _private->eventKeyTapGesture;
			break;
		case Leap::Gesture::TYPE_SCREEN_TAP:
			if (_private->eventScreenTapGesture == NULL)
				_private->eventScreenTapGesture = NewObject<UScreenTapGesture>(this);
			_private->eventScreenTapGesture->setGesture(Leap::ScreenTapGesture(gesture));
			ILeapEventInterface::Execute_ScreenTapGestureDetected(_private->interfaceDelegate, _private->eventScreenTapGesture);
			_private->eventGesture = _private->eventScreenTapGesture;
			break;
		case Leap::Gesture::TYPE_SWIPE:
			if (_private->eventSwipeGesture == NULL)
				_private->eventSwipeGesture = NewObject<USwipeGesture>(this);
			_private->eventSwipeGesture->setGesture(Leap::SwipeGesture(gesture));
			ILeapEventInterface::Execute_SwipeGestureDetected(_private->interfaceDelegate, _private->eventSwipeGesture);
			_private->eventGesture = _private->eventSwipeGesture;
			break;
		default:
			break;
		}

		//emit gesture
		if (type != Leap::Gesture::TYPE_INVALID)
		{
			ILeapEventInterface::Execute_GestureDetected(_private->interfaceDelegate, _private->eventGesture);
		}
	}
}

#undef LOCTEXT_NAMESPACE
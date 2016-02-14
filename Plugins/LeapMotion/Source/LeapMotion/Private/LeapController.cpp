#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"
#include "SlateBasics.h"
#include <vector>

#include <sstream> //for std::stringstream 
#include <string>  //for std::string

//#include "ILeapMotion.h"

#define LEAP_IM_SCALE 0.01111111111 //this is 1/90. We consider 90 degrees to be 1.0 for Input mapping

//Global controller count, temporary debug variable since the plugin does not support more than one component. We track it and warn the users.
int ControllerCount = 0;

//Input mapping - FKey declarations
//Define each FKey const in a .cpp so we can compile
const FKey EKeysLeap::LeapLeftPinch("LeapLeftPinch");
const FKey EKeysLeap::LeapLeftGrab("LeapLeftGrab");
const FKey EKeysLeap::LeapLeftPalmPitch("LeapLeftPalmPitch");
const FKey EKeysLeap::LeapLeftPalmYaw("LeapLeftPalmYaw");
const FKey EKeysLeap::LeapLeftPalmRoll("LeapLeftPalmRoll");

const FKey EKeysLeap::LeapRightPinch("LeapRightPinch");
const FKey EKeysLeap::LeapRightGrab("LeapRightGrab");
const FKey EKeysLeap::LeapRightPalmPitch("LeapRightPalmPitch");
const FKey EKeysLeap::LeapRightPalmYaw("LeapRightPalmYaw");
const FKey EKeysLeap::LeapRightPalmRoll("LeapRightPalmRoll");

//UE v4.6 IM event wrappers
bool EmitKeyUpEventForKey(FKey Key, int32 User, bool Repeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool EmitKeyDownEventForKey(FKey Key, int32 User, bool Repeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool EmitAnalogInputEventForKey(FKey Key, float Value, int32 User, bool Repeat)
{
	FAnalogInputEvent AnalogInputEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0, Value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}


//Used for Reliable State Tracking
struct LeapHandStateData{
	bool Grabbed;
	bool Pinched;
	int32 FingerCount;
	int32 Id;
};

class LeapStateData{
public:
	bool HasStateForId(int32 HandId, LeapHandStateData& State);
	LeapHandStateData StateForId(int32 HandId);
	void SetStateForId(LeapHandStateData HandState, int32 HandId);

	std::vector<LeapHandStateData> HandStates;
	int32 HandCount;
};

//LeapStateData
bool LeapStateData::HasStateForId(int32 HandId, LeapHandStateData& State)
{
	for (size_t i = 0; i < HandStates.size(); ++i) {
		// If two hand pointers compare equal, they refer to the same hand device.
		if (HandStates[i].Id == HandId) {
			State = HandStates[i];
			return true;
		}
	}
	return false;
}

LeapHandStateData LeapStateData::StateForId(int32 HandId)
{
	LeapHandStateData HandState;
	if (!HasStateForId(HandId, HandState)){
		HandState.Id = HandId;
		HandStates.push_back(HandState);
	}

	return HandState;
}

void LeapStateData::SetStateForId(LeapHandStateData HandState, int32 HandId)
{
	for (size_t i = 0; i < HandStates.size(); ++i) {
		// If two hand pointers compare equal, they refer to the same hand device.
		if (HandStates[i].Id == HandId) {
			HandStates[i] = HandState;
		}
	}
}

class LeapControllerPrivate
{
public:
	~LeapControllerPrivate()
	{
		if(!CleanupCalled)
			CleanupEventData();
	}

	//Ensures our rooted objects are unrooted so they can be GC'd
	void CleanupEventData()
	{
		if (EventHand)
		{
			EventHand->CleanupRootReferences();
		}
		if (EventFinger)
		{
			EventFinger->CleanupRootReferences();
		}
		if (EventGesture)
		{
			EventGesture->CleanupRootReferences();
		}
		if (EventCircleGesture)
		{
			EventCircleGesture->CleanupRootReferences();
		}
		if (EventKeyTapGesture)
		{
			EventKeyTapGesture->CleanupRootReferences();
		}
		if (EventScreenTapGesture)
		{
			EventScreenTapGesture->CleanupRootReferences();
		}
		if (EventSwipeGesture)
		{
			EventSwipeGesture->CleanupRootReferences();
		}
		if (EventImage1)
		{
			EventImage1->CleanupRootReferences();
		}
		if (EventImage2)
		{
			EventImage2->CleanupRootReferences();
		}
		if (Frame)
		{
			Frame->CleanupRootReferences();
		}
		CleanupCalled = true;
		UE_LOG(LeapPluginLog, Log, TEXT("LeapController::CleanupEventData Delete Called"));
	}
	bool CleanupCalled = false;

	//Properties and Pointers
	LeapStateData PastState;
	Leap::Controller Leap;
	ULeapFrame* Frame = NULL;

	//Event UObjects, we have to manage memory for these to stop leaks
	ULeapHand* EventHand = NULL;
	ULeapFinger* EventFinger = NULL;
	ULeapGesture* EventGesture = NULL;
	ULeapCircleGesture* EventCircleGesture = NULL;
	ULeapKeyTapGesture* EventKeyTapGesture = NULL;
	ULeapScreenTapGesture* EventScreenTapGesture = NULL;
	ULeapSwipeGesture* EventSwipeGesture = NULL;
	ULeapImage* EventImage1 = NULL;
	ULeapImage* EventImage2 = NULL;
	
	UObject* InterfaceDelegate = NULL;	//NB they have to be set to null manually or MSFT will set them to CDCDCDCD...
	bool OptimizeForHMD = false;
	bool AllowImages = false;
	bool UseGammaCorrection = false;
	bool ImageEventsEnabled = false;
	bool UseMountOffset = true;

	//Functions
	void SetPolicyStatus(Leap::Controller::PolicyFlag Flag, bool Status);
	void SetPolicyFlagsFromBools();
};

//LeapControllerPrivate
void LeapControllerPrivate::SetPolicyStatus(Leap::Controller::PolicyFlag Flag, bool Status)
{
	if (Status)
		Leap.setPolicy(Flag);
	else
		Leap.clearPolicy(Flag);
}

void LeapControllerPrivate::SetPolicyFlagsFromBools()
{
	SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD, OptimizeForHMD);
	SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_IMAGES, AllowImages);
}

//ULeapController
ULeapController::ULeapController(const FObjectInitializer &ObjectInitializer) : UActorComponent(ObjectInitializer), Private(new LeapControllerPrivate())
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to
}

ULeapController::~ULeapController()
{
	delete Private;
}

bool ULeapController::IsConnected() const
{
	return Private->Leap.isConnected();
}

void ULeapController::OnRegister()
{
	Super::OnRegister();

	//Attach the delegate pointer automatically
	SetInterfaceDelegate(GetOwner());

	//Track and warn users about multiple components. - Removed for now.
	ControllerCount++;
	//if (controllerCount>1)
		//UE_LOG(LeapPluginLog, Warning, TEXT("Warning! More than one (%d) Leap Controller Component detected! Duplication of work and output may result (inefficiency warning)."), controllerCount);

	//UE_LOG(LeapPluginLog, Log, TEXT("Registered Leap Component(%d)."), controllerCount);
}

void ULeapController::OnUnregister()
{
	//Allow GC of private UObject data
	Private->CleanupEventData();	//UObjects attached to root need to be unrooted before we unregister so we do not crash between pie sessions (or without attaching to this object, leak them)
	ControllerCount--;

	Super::OnUnregister();
	//UE_LOG(LeapPluginLog, Log, TEXT("Unregistered Leap Component(%d)."), controllerCount);
}

void ULeapController::TickComponent(float DeltaTime, enum ELevelTick TickType,
									FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Forward the component tick
	InterfaceEventTick(DeltaTime);
}

ULeapFrame* ULeapController::Frame(int32 History)
{
	if (Private->Frame == NULL)
	{
		Private->Frame = NewObject<ULeapFrame>(this, ULeapFrame::StaticClass());
		Private->Frame->SetFlags(RF_RootSet);
	}
	Private->Frame->SetFrame(Private->Leap, History);
	return (Private->Frame);
}

bool ULeapController::HasFocus() const
{
	return (Private->Leap.hasFocus());
}

bool ULeapController::IsServiceConnected() const
{
	return (Private->Leap.isServiceConnected());
}


void ULeapController::OptimizeForHMD(bool useTopdown, bool autoRotate, bool autoShift)
{
	//Set Policy Optimization
	Private->OptimizeForHMD = useTopdown;
	Private->SetPolicyFlagsFromBools();

	//Pass adjustment booleans
	if (useTopdown)
		LeapSetShouldAdjustForFacing(true);
	else
		LeapSetShouldAdjustForFacing(false);

	LeapSetShouldAdjustForHMD(autoRotate, autoShift);
	LeapSetShouldAdjustForMountOffset(Private->UseMountOffset);	//this function defaults to true at the moment, can be changed via command
}

void ULeapController::EnableImageSupport(bool allowImages, bool emitImageEvents, bool useGammaCorrection)
{
	Private->UseGammaCorrection = useGammaCorrection;
	Private->AllowImages = allowImages;
	Private->SetPolicyFlagsFromBools();
	Private->ImageEventsEnabled = emitImageEvents;
}

void ULeapController::EnableBackgroundTracking(bool trackInBackground)
{
	Private->SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES, trackInBackground);
}

void ULeapController::EnableGesture(LeapGestureType type, bool enable)
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

	Private->Leap.enableGesture(rawType, enable);
}


void ULeapController::SetLeapMountToHMDOffset(FVector Offset)
{
	if (Offset == FVector(0, 0, 0))
	{
		Private->UseMountOffset = false;
		LeapSetShouldAdjustForMountOffset(Private->UseMountOffset);
	}
	else
	{
		Private->UseMountOffset = true;
		LeapSetShouldAdjustForMountOffset(Private->UseMountOffset);
		LeapSetMountToHMDOffset(Offset);
	}
}

//Leap Event Interface - Event Driven System
void ULeapController::SetInterfaceDelegate(UObject* NewDelegate)
{
	UE_LOG(LeapPluginLog, Log, TEXT("InterfaceObject: %s"), *NewDelegate->GetName());

	//Use this format to support both blueprint and C++ form
	if (NewDelegate->GetClass()->ImplementsInterface(ULeapEventInterface::StaticClass()))
	{
		Private->InterfaceDelegate = NewDelegate;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("LeapController Warning: Delegate is NOT set, did you implement LeapEventInterface?"));
	}
}

//Utility
bool HandClosed(float Strength)
{
	return (Strength == 1.f);
}

bool HandPinched(float Strength)
{
	return (Strength > 0.8);
}

bool HandForId(int32 CheckId, Leap::HandList Hands, Leap::Hand& ReturnHand)
{
	for (int i = 0; i < Hands.count(); i++)
	{
		Leap::Hand Hand = Hands[i];
		if (CheckId == Hand.id())
		{
			ReturnHand = Hand;
			return true;
		}
	}
	return false;
}



//Main Event driven tick
void ULeapController::InterfaceEventTick(float DeltaTime)
{
	//This is our tick event that is forwarded from the delegate, check validity
	if (!Private->InterfaceDelegate)
	{
		return;
	}

	//Pointers
	Leap::Frame Frame = Private->Leap.frame();
	Leap::Frame PastFrame = Private->Leap.frame(1);

	//-Hands-

	//Hand Count
	int HandCount = Frame.hands().count();

	if (Private->PastState.HandCount != HandCount)
	{
		ILeapEventInterface::Execute_HandCountChanged(Private->InterfaceDelegate, HandCount);
		
		//Zero our input mapping orientations (akin to letting go of a joystick)
		if (HandCount == 0)
		{
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmPitch, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmYaw, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmRoll, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmPitch, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmYaw, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmRoll, 0, 0, 0);
		}
	}

	//Cycle through each hand
	for (int i = 0; i < HandCount; i++)
	{
		Leap::Hand Hand = Frame.hands()[i];
		LeapHandStateData PastHandState = Private->PastState.StateForId(Hand.id());		//we use a custom class to hold reliable state tracking based on id's

		//Make a ULeapHand
		if (Private->EventHand == NULL)
		{
			Private->EventHand = NewObject<ULeapHand>(this);
			Private->EventHand->SetFlags(RF_RootSet);
		}
		Private->EventHand->SetHand(Hand);

		//Emit hand
		ILeapEventInterface::Execute_LeapHandMoved(Private->InterfaceDelegate, Private->EventHand);

		//Left/Right hand forwarding
		if (Hand.isRight())
		{
			ILeapEventInterface::Execute_LeapRightHandMoved(Private->InterfaceDelegate, Private->EventHand);
			//Input Mapping
			FRotator PalmOrientation = Private->EventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		} else if (Hand.isLeft())
		{
			ILeapEventInterface::Execute_LeapLeftHandMoved(Private->InterfaceDelegate, Private->EventHand);
			//Input Mapping
			FRotator PalmOrientation = Private->EventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		}

		//Grabbing
		float GrabStrength = Hand.grabStrength();
		bool Grabbed = HandClosed(GrabStrength);

		if (Grabbed) 
		{
			ILeapEventInterface::Execute_LeapHandGrabbing(Private->InterfaceDelegate, GrabStrength, Private->EventHand);
		}

		if (Grabbed && !PastHandState.Grabbed)
		{
			ILeapEventInterface::Execute_LeapHandGrabbed(Private->InterfaceDelegate, GrabStrength, Private->EventHand);
			
			//input mapping
			if (Private->EventHand->HandType == LeapHandType::HAND_LEFT)
			{
				EmitKeyDownEventForKey(EKeysLeap::LeapLeftGrab, 0, 0);
			}
			else
			{
				EmitKeyDownEventForKey(EKeysLeap::LeapRightGrab, 0, 0);
			}
		}
		else if (!Grabbed && PastHandState.Grabbed)
		{
			ILeapEventInterface::Execute_LeapHandReleased(Private->InterfaceDelegate, GrabStrength, Private->EventHand);

			//input mapping
			if (Private->EventHand->HandType == LeapHandType::HAND_LEFT)
			{
				EmitKeyUpEventForKey(EKeysLeap::LeapLeftGrab, 0, 0);
			}
			else
			{
				EmitKeyUpEventForKey(EKeysLeap::LeapRightGrab, 0, 0);
			}
		}

		//Pinching
		float PinchStrength = Hand.pinchStrength();
		bool Pinched = HandPinched(PinchStrength);

		//While grabbing disable pinching detection, this helps to reduce spam as pose confidence plummets
		if (Grabbed)
		{
			Pinched = PastHandState.Pinched;
		}
		else
		{
			if (Pinched)
			{
				ILeapEventInterface::Execute_LeapHandPinching(Private->InterfaceDelegate, PinchStrength, Private->EventHand);
			}
			if (Pinched && !PastHandState.Pinched)
			{
				ILeapEventInterface::Execute_LeapHandPinched(Private->InterfaceDelegate, PinchStrength, Private->EventHand);
				//input mapping
				if (Private->EventHand->HandType == LeapHandType::HAND_LEFT)
				{
					EmitKeyDownEventForKey(EKeysLeap::LeapLeftPinch, 0, 0);
				}
				else
				{
					EmitKeyDownEventForKey(EKeysLeap::LeapRightPinch, 0, 0);
				}
			}
			else if (!Pinched && PastHandState.Pinched)
			{
				ILeapEventInterface::Execute_LeapHandUnpinched(Private->InterfaceDelegate, PinchStrength, Private->EventHand);
				//input mapping
				if (Private->EventHand->HandType == LeapHandType::HAND_LEFT)
				{
					EmitKeyUpEventForKey(EKeysLeap::LeapLeftPinch, 0, 0);
				}
				else
				{
					EmitKeyUpEventForKey(EKeysLeap::LeapRightPinch, 0, 0);
				}
			}
		}

		//-Fingers-
		Leap::FingerList Fingers = Hand.fingers();

		//Count
		int FingerCount = Fingers.count();
		if ((PastHandState.FingerCount != FingerCount))
		{
			ILeapEventInterface::Execute_FingerCountChanged(Private->InterfaceDelegate, FingerCount);
		}
		if (Private->EventFinger == NULL)
		{
			Private->EventFinger = NewObject<ULeapFinger>(this);
			Private->EventFinger->SetFlags(RF_RootSet);
		}

		Leap::Finger Finger;

		//Cycle through each finger
		for (int j = 0; j < FingerCount; j++)
		{
			Finger = Fingers[j];
			Private->EventFinger->SetFinger(Finger);

			//Finger Moved
			if (Finger.isValid())
				ILeapEventInterface::Execute_LeapFingerMoved(Private->InterfaceDelegate, Private->EventFinger);
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		Finger = Fingers.leftmost();
		Private->EventFinger->SetFinger(Finger);
		ILeapEventInterface::Execute_LeapLeftMostFingerMoved(Private->InterfaceDelegate, Private->EventFinger);

		//Rightmost
		Finger = Fingers.rightmost();
		Private->EventFinger->SetFinger(Finger);
		ILeapEventInterface::Execute_LeapRightMostFingerMoved(Private->InterfaceDelegate, Private->EventFinger);

		//Frontmost
		Finger = Fingers.frontmost();
		Private->EventFinger->SetFinger(Finger);
		ILeapEventInterface::Execute_LeapFrontMostFingerMoved(Private->InterfaceDelegate, Private->EventFinger);

		//touch only for front-most finger, most common use case
		float touchDistance = Finger.touchDistance();
		if (touchDistance <= 0.f)
		{
			ILeapEventInterface::Execute_LeapFrontFingerTouch(Private->InterfaceDelegate, Private->EventFinger);
		}

		//Set the state data for next cycle
		PastHandState.Grabbed = Grabbed;
		PastHandState.Pinched = Pinched;
		PastHandState.FingerCount = FingerCount;

		Private->PastState.SetStateForId(PastHandState, Hand.id());
	}

	Private->PastState.HandCount = HandCount;

	//Gestures
	for (int i = 0; i < Frame.gestures().count(); i++)
	{
		Leap::Gesture Gesture = Frame.gestures()[i];
		Leap::Gesture::Type Type = Gesture.type();

		switch (Type)
		{
		case Leap::Gesture::TYPE_CIRCLE:
			if (Private->EventCircleGesture == NULL){
				Private->EventCircleGesture = NewObject<ULeapCircleGesture>(this);
				Private->EventCircleGesture->SetFlags(RF_RootSet);
			}
			Private->EventCircleGesture->SetGesture(Leap::CircleGesture(Gesture));
			ILeapEventInterface::Execute_CircleGestureDetected(Private->InterfaceDelegate, Private->EventCircleGesture);
			Private->EventGesture = Private->EventCircleGesture;
			break;
		case Leap::Gesture::TYPE_KEY_TAP:
			if (Private->EventKeyTapGesture == NULL)
			{
				Private->EventKeyTapGesture = NewObject<ULeapKeyTapGesture>(this);
				Private->EventKeyTapGesture->SetFlags(RF_RootSet);
			}
			Private->EventKeyTapGesture->SetGesture(Leap::KeyTapGesture(Gesture));
			ILeapEventInterface::Execute_KeyTapGestureDetected(Private->InterfaceDelegate, Private->EventKeyTapGesture);
			Private->EventGesture = Private->EventKeyTapGesture;
			break;
		case Leap::Gesture::TYPE_SCREEN_TAP:
			if (Private->EventScreenTapGesture == NULL)
			{
				Private->EventScreenTapGesture = NewObject<ULeapScreenTapGesture>(this);
				Private->EventScreenTapGesture->SetFlags(RF_RootSet);
			}
			Private->EventScreenTapGesture->SetGesture(Leap::ScreenTapGesture(Gesture));
			ILeapEventInterface::Execute_ScreenTapGestureDetected(Private->InterfaceDelegate, Private->EventScreenTapGesture);
			Private->EventGesture = Private->EventScreenTapGesture;
			break;
		case Leap::Gesture::TYPE_SWIPE:
			if (Private->EventSwipeGesture == NULL)
			{
				Private->EventSwipeGesture = NewObject<ULeapSwipeGesture>(this);
				Private->EventSwipeGesture->SetFlags(RF_RootSet);
			}
			Private->EventSwipeGesture->SetGesture(Leap::SwipeGesture(Gesture));
			ILeapEventInterface::Execute_SwipeGestureDetected(Private->InterfaceDelegate, Private->EventSwipeGesture);
			Private->EventGesture = Private->EventSwipeGesture;
			break;
		default:
			break;
		}

		//emit gesture
		if (Type != Leap::Gesture::TYPE_INVALID)
		{
			ILeapEventInterface::Execute_GestureDetected(Private->InterfaceDelegate, Private->EventGesture);
		}
	}

	//Image
	if (Private->AllowImages && Private->ImageEventsEnabled)
	{
		int ImageCount = Frame.images().count();
		for (int i = 0; i < ImageCount; i++)
		{
			Leap::Image Image = Frame.images()[i];

			//Loop modification - Only emit 0 and 1, use two different pointers so we can get different images
			if (i == 0)
			{
				if (Private->EventImage1 == NULL)
				{
					Private->EventImage1 = NewObject<ULeapImage>(this);
					Private->EventImage1->SetFlags(RF_RootSet);
				}
				Private->EventImage1->UseGammaCorrection = Private->UseGammaCorrection;
				Private->EventImage1->SetLeapImage(Image);

				ILeapEventInterface::Execute_RawImageReceived(Private->InterfaceDelegate, Private->EventImage1->Texture(), Private->EventImage1);
			}
			else if (i == 1)
			{
				if (Private->EventImage2 == NULL)
                {
					Private->EventImage2 = NewObject<ULeapImage>(this);
					Private->EventImage2->SetFlags(RF_RootSet);
				}
				Private->EventImage2->UseGammaCorrection = Private->UseGammaCorrection;
				Private->EventImage2->SetLeapImage(Image);

				ILeapEventInterface::Execute_RawImageReceived(Private->InterfaceDelegate, Private->EventImage2->Texture(), Private->EventImage2);
			}
		}
	}
}
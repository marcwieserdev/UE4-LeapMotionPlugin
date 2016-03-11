#include "LeapMotionPrivatePCH.h"
#include "IHeadMountedDisplay.h"
#include "LeapEventInterface.h"
#include "FLeapMotionInputDevice.h"
#include "LeapHand.h"
#include "LeapBaseObject.h"
#include "LeapHMDSnapshot.h"
#include "LeapC.h"

#define LEAP_IM_SCALE 0.01111111111 //this is 1/90. We consider 90 degrees to be 1.0 for Input mapping
#define MAX_HMD_SNAPSHOT_COUNT 20

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

/**
* Keep last 20 samples for finding the closest sample to a specified timestamp
*/
class HMDSnapshotSamples
{
public:
	HMDSnapshotSamples(Leap::Controller InController) : LeapController(InController) {};

	//Timewarp utility methods
	void AddCurrentHMDSample();
	LeapHMDSnapshot CurrentHMDSample();
	LeapHMDSnapshot LastHMDSample();
	LeapHMDSnapshot& HMDSampleClosestToTimestamp(int64 Timestamp);

	Leap::Controller& LeapController;
private:
	LeapHMDSnapshot Samples[MAX_HMD_SNAPSHOT_COUNT];
	int CurrentIndex = 0;
};

void HMDSnapshotSamples::AddCurrentHMDSample()
{
	//Grab current sample
	Samples[CurrentIndex] = CurrentHMDSample();

	//Circular tracker - slot it in correctly
	CurrentIndex++;
	if (CurrentIndex >= MAX_HMD_SNAPSHOT_COUNT)
	{
		CurrentIndex = 0;
	}
}

LeapHMDSnapshot HMDSnapshotSamples::CurrentHMDSample()
{
	LeapHMDSnapshot Snapshot;

	//we use leap time stamps to keep things consistent
	//Snapshot.Timestamp = LeapController.now();		//This is missing from current leap 3.1 api in LeapC++ api!
	Snapshot.Timestamp = LeapGetNow();					//Workaround use LeapC api
	Snapshot.Orientation;
	Snapshot.Position;

	GEngine->HMDDevice->GetCurrentOrientationAndPosition(Snapshot.Orientation, Snapshot.Position);
	return Snapshot;
}


LeapHMDSnapshot HMDSnapshotSamples::LastHMDSample()
{
	return Samples[CurrentIndex];
}

LeapHMDSnapshot& HMDSnapshotSamples::HMDSampleClosestToTimestamp(int64 Timestamp)
{
	int64 MinDifference = INT64_MAX;
	int32 MinIndex = 0;	//always have a valid index in case something goes wrong

	//UE_LOG(LeapPluginLog, Log, TEXT("Timewarp Debug - Now: %d"), Timestamp);

	for (int32 i = 0; i < MAX_HMD_SNAPSHOT_COUNT; i++)
	{
		LeapHMDSnapshot& Snapshot = Samples[i];
		int32 Difference = FMath::Abs(Snapshot.Timestamp - Timestamp);

		//UE_LOG(LeapPluginLog, Log, TEXT("Timewarp Debug - Snapshot: %d, Difference: %d"), Snapshot.Timestamp, Difference);

		if (Difference < MinDifference)
		{
			MinDifference = Difference;
			MinIndex = i;
		}
	}
	//UE_LOG(LeapPluginLog, Log, TEXT("Timewarp Debug - MinSnapshot: %d, MinDifference: %d"), Samples[MinIndex].Timestamp, MinDifference);
	return Samples[MinIndex];
}

//Function call Utility
void FLeapMotionInputDevice::CallFunctionOnDelegates(TFunction< void(UObject*)> InFunction)
{
	for (UObject* EventDelegate : EventDelegates)
	{
		InFunction(EventDelegate);
	}
}

//UE v4.6 IM event wrappers
bool FLeapMotionInputDevice::EmitKeyUpEventForKey(FKey Key, int32 User, bool Repeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool FLeapMotionInputDevice::EmitKeyDownEventForKey(FKey Key, int32 User, bool Repeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool FLeapMotionInputDevice::EmitAnalogInputEventForKey(FKey Key, float Value, int32 User, bool Repeat)
{
	FAnalogInputEvent AnalogInputEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, Repeat, 0, 0, Value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}

//Utility
bool FLeapMotionInputDevice::HandClosed(float Strength)
{
	return (Strength == 1.f);
}

bool FLeapMotionInputDevice::HandPinched(float Strength)
{
	return (Strength > 0.8);
}

bool FLeapMotionInputDevice::HandForId(int32 CheckId, Leap::HandList Hands, Leap::Hand& ReturnHand)
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

//Used for Reliable State Tracking
struct LeapHandStateData {
	bool Grabbed;
	bool Pinched;
	int32 FingerCount;
	int32 Id;
};

//LeapStateData
class LeapStateData {
public:
	bool HasStateForId(int32 HandId, LeapHandStateData& State);
	LeapHandStateData StateForId(int32 HandId);
	void SetStateForId(LeapHandStateData HandState, int32 HandId);

	std::vector<LeapHandStateData> HandStates;
	int32 HandCount;
};

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
	if (!HasStateForId(HandId, HandState)) {
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

FLeapMotionInputDevice::FLeapMotionInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) : MessageHandler(InMessageHandler) 
{
	PastState = new LeapStateData;
	HMDSamples = new HMDSnapshotSamples(ControllerData.LeapController); 	//store a reference for our timing circuits

	//PRoot = NewObject<ULeapBaseObject>();
	//PRoot->AddToRoot();  //work around to keep our custom event objects in memory until we're done with them
}


void FLeapMotionInputDevice::Tick(float DeltaTime)
{
	//Add HMD samples when you tick for timewarp



}


//Main loop event emitter
void FLeapMotionInputDevice::SendControllerEvents()
{
	HMDSamples->AddCurrentHMDSample();
	ParseEvents();
}

void FLeapMotionInputDevice::ParseEvents()
{
	//Optimization: If we don't have any delegates, skip
	if (EventDelegates.Num() == 0)
	{
		return;
	}

	//Pointers
	Leap::Frame Frame = ControllerData.LeapController.frame();
	Leap::Frame PastFrame = ControllerData.LeapController.frame(1);

	//Calculate HMD Timewarp if valid
	if (GEngine->HMDDevice.IsValid() && ControllerData.bTimeWarpEnabled) {
		LeapHMDSnapshot ThenSnapshot = HMDSamples->HMDSampleClosestToTimestamp(Frame.timestamp());
		LeapHMDSnapshot NowSnapShot = HMDSamples->CurrentHMDSample();

		LeapHMDSnapshot HistorySnapshot = HMDSamples->LastHMDSample();	//reduce jitter
		//ControllerData.TimeWarpSnapshot = NowSnapShot.Difference(ThenSnapshot, ControllerData.TimeWarpFactor);// * ControllerData.TimeWarpFactor;

		FQuat WarpQuat = NowSnapShot.Orientation;//FQuat::Slerp(NowSnapShot.Orientation, HistorySnapshot.Orientation, ControllerData.TimeWarpTween);
		FQuat ThenTweened = FQuat::Slerp(ThenSnapshot.Orientation, HistorySnapshot.Orientation, ControllerData.TimeWarpTween);

		ControllerData.TimeWarpSnapshot.Orientation = (WarpQuat.Inverse() * ControllerData.TimeWarpFactor) * ThenTweened;

		ControllerData.TimeWarpAmountMs = (ControllerData.TimeWarpSnapshot.Timestamp) / 1000.f;
	}

	//-Hands-

	//Hand Count
	int HandCount = Frame.hands().count();

	if (PastState->HandCount != HandCount)
	{
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_HandCountChanged(EventDelegate, HandCount);
		});
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
		LeapHandStateData PastHandState = PastState->StateForId(Hand.id());		//we use a custom class to hold reliable state tracking based on id's

																				//Make a ULeapHand
		if (PEventHand == nullptr)
		{
			PEventHand = NewObject<ULeapHand>();
			PEventHand->AddToRoot();
		}
		PEventHand->SetHand(Hand);

		//Emit hand
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapHandMoved(EventDelegate, PEventHand);
		});


		//Left/Right hand forwarding
		if (Hand.isRight())
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapRightHandMoved(EventDelegate, PEventHand);
			});

			//Input Mapping
			FRotator PalmOrientation = PEventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		}
		else if (Hand.isLeft())
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapLeftHandMoved(EventDelegate, PEventHand);
			});

			//Input Mapping
			FRotator PalmOrientation = PEventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		}

		//Grabbing
		float GrabStrength = Hand.grabStrength();
		bool Grabbed = HandClosed(GrabStrength);

		if (Grabbed)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandGrabbing(EventDelegate, GrabStrength, PEventHand);
			});

		}

		if (Grabbed && !PastHandState.Grabbed)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandGrabbed(EventDelegate, GrabStrength, PEventHand);
			});

			//input mapping
			if (PEventHand->HandType == LeapHandType::HAND_LEFT)
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
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandReleased(EventDelegate, GrabStrength, PEventHand);
			});

			//input mapping
			if (PEventHand->HandType == LeapHandType::HAND_LEFT)
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
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandPinching(EventDelegate, PinchStrength, PEventHand);
				});
			}
			if (Pinched && !PastHandState.Pinched)
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandPinched(EventDelegate, PinchStrength, PEventHand);
				});
				//input mapping
				if (PEventHand->HandType == LeapHandType::HAND_LEFT)
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
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandUnpinched(EventDelegate, PinchStrength, PEventHand);
				});
				//input mapping
				if (PEventHand->HandType == LeapHandType::HAND_LEFT)
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
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_FingerCountChanged(EventDelegate, FingerCount);
			});
		}
		if (PEventFinger == nullptr)
		{
			PEventFinger = NewObject<ULeapFinger>();
			PEventFinger->AddToRoot();
		}

		Leap::Finger Finger;

		//Cycle through each finger
		for (int j = 0; j < FingerCount; j++)
		{
			Finger = Fingers[j];
			PEventFinger->SetFinger(Finger);

			//Finger Moved
			if (Finger.isValid())
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapFingerMoved(EventDelegate, PEventFinger);
				});
			}
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		Finger = Fingers.leftmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapLeftMostFingerMoved(EventDelegate, PEventFinger);
		});

		//Rightmost
		Finger = Fingers.rightmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapRightMostFingerMoved(EventDelegate, PEventFinger);
		});

		//Frontmost
		Finger = Fingers.frontmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapFrontMostFingerMoved(EventDelegate, PEventFinger);
		});

		//touch only for front-most finger, most common use case
		float touchDistance = Finger.touchDistance();
		if (touchDistance <= 0.f)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapFrontFingerTouch(EventDelegate, PEventFinger);
			});
		}

		//Set the state data for next cycle
		PastHandState.Grabbed = Grabbed;
		PastHandState.Pinched = Pinched;
		PastHandState.FingerCount = FingerCount;

		PastState->SetStateForId(PastHandState, Hand.id());
	}

	PastState->HandCount = HandCount;

	//Gestures
	for (int i = 0; i < Frame.gestures().count(); i++)
	{
		Leap::Gesture Gesture = Frame.gestures()[i];
		Leap::Gesture::Type Type = Gesture.type();

		switch (Type)
		{
		case Leap::Gesture::TYPE_CIRCLE:
			if (PEventCircleGesture == nullptr)
			{
				PEventCircleGesture = NewObject<ULeapCircleGesture>();
				PEventCircleGesture->AddToRoot();
			}
			PEventCircleGesture->SetGesture(Leap::CircleGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_CircleGestureDetected(EventDelegate, PEventCircleGesture);
			});
			PEventGesture = PEventCircleGesture;
			break;
		case Leap::Gesture::TYPE_KEY_TAP:
			if (PEventKeyTapGesture == nullptr)
			{
				PEventKeyTapGesture = NewObject<ULeapKeyTapGesture>();
				PEventKeyTapGesture->AddToRoot();
			}
			PEventKeyTapGesture->SetGesture(Leap::KeyTapGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_KeyTapGestureDetected(EventDelegate, PEventKeyTapGesture);
			});
			PEventGesture = PEventKeyTapGesture;
			break;
		case Leap::Gesture::TYPE_SCREEN_TAP:
			if (PEventScreenTapGesture == nullptr)
			{
				PEventScreenTapGesture = NewObject<ULeapScreenTapGesture>();
				PEventScreenTapGesture->AddToRoot();
			}
			PEventScreenTapGesture->SetGesture(Leap::ScreenTapGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_ScreenTapGestureDetected(EventDelegate, PEventScreenTapGesture);
			});
			PEventGesture = PEventScreenTapGesture;
			break;
		case Leap::Gesture::TYPE_SWIPE:
			if (PEventSwipeGesture == nullptr)
			{
				PEventSwipeGesture = NewObject<ULeapSwipeGesture>();
				PEventSwipeGesture->AddToRoot();
			}
			PEventSwipeGesture->SetGesture(Leap::SwipeGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_SwipeGestureDetected(EventDelegate, PEventSwipeGesture);
			});
			PEventGesture = PEventSwipeGesture;
			break;
		default:
			break;
		}

		//emit gesture
		if (Type != Leap::Gesture::TYPE_INVALID)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_GestureDetected(EventDelegate, PEventGesture);
			});
		}
	}

	//Image
	if (ControllerData.bAllowImageEvents && ControllerData.bImageEventsEnabled)
	{
		int ImageCount = Frame.images().count();

		//We only support getting both images
		if (ImageCount >= 2)
		{
			Leap::Image Image1 = Frame.images()[0];
			if (PEventImage1 == nullptr)
			{
				PEventImage1 = NewObject<ULeapImage>();
				PEventImage1->AddToRoot();
			}
			PEventImage1->UseGammaCorrection = ControllerData.bUseGammaCorrection;
			PEventImage1->SetLeapImage(Image1);

			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_RawImageReceived(EventDelegate, PEventImage1->Texture(), PEventImage1);
			});

			Leap::Image Image2 = Frame.images()[1];
			if (PEventImage2 == nullptr)
			{
				PEventImage2 = NewObject<ULeapImage>();
				PEventImage2->AddToRoot();
			}
			PEventImage2->UseGammaCorrection = ControllerData.bUseGammaCorrection;
			PEventImage2->SetLeapImage(Image2);

			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_RawImageReceived(EventDelegate, PEventImage2->Texture(), PEventImage2);
			});
		}
	}
}

void FLeapMotionInputDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FLeapMotionInputDevice::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
	return false;
}


void FLeapMotionInputDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}


void FLeapMotionInputDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values)
{
	// Nothing necessary to do (boilerplate code to complete the interface)
}

void FLeapMotionInputDevice::ClearReferences(UObject* object)
{
	if (object != nullptr)
	{
		if (object->IsValidLowLevel())
		{
			object->RemoveFromRoot();
			object->MarkPendingKill();
		}
	}
}

FLeapMotionInputDevice::~FLeapMotionInputDevice()
{
	delete PastState;
	delete HMDSamples;

	//TODO: cleaner memory handling for event objects, any ideas?
	//ClearReferences(PRoot);
	ClearReferences(PEventHand);
	ClearReferences(PEventFinger);
	ClearReferences(PEventGesture);
	ClearReferences(PEventCircleGesture);
	ClearReferences(PEventKeyTapGesture);
	ClearReferences(PEventScreenTapGesture);
	ClearReferences(PEventSwipeGesture);
	ClearReferences(PEventImage1);
	ClearReferences(PEventImage2);
	PEventHand = nullptr;
	PEventFinger = nullptr;
	PEventGesture = nullptr;
	PEventCircleGesture = nullptr;
	PEventKeyTapGesture = nullptr;
	PEventScreenTapGesture = nullptr;
	PEventSwipeGesture = nullptr;
	PEventImage1 = nullptr;
	PEventImage2 = nullptr;
	PEventImage2 = nullptr;
	

}

void FLeapMotionInputDevice::AddEventDelegate(UObject* EventDelegate)
{
	if (EventDelegate->GetClass()->ImplementsInterface(ULeapEventInterface::StaticClass()))
		EventDelegates.Add(EventDelegate);

	UE_LOG(LeapPluginLog, Log, TEXT("AddEventDelegate (%d)."), EventDelegates.Num());
}

void FLeapMotionInputDevice::RemoveEventDelegate(UObject* EventDelegate)
{
	EventDelegates.Remove(EventDelegate);

	UE_LOG(LeapPluginLog, Log, TEXT("RemoveEventDelegate (%d)."), EventDelegates.Num());
}

#include "LeapMotionPrivatePCH.h"

class PrivateGesture
{
public:
	~PrivateGesture()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		if (Frame)
		{
			Frame->CleanupRootReferences();
		}
		if (Hands)
		{
			Hands->CleanupRootReferences();
		}
		if (Pointables)
		{
			Pointables->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::Gesture Gesture;
	ULeapFrame* Frame = NULL;
	ULeapHandList* Hands = NULL;
	ULeapPointableList* Pointables = NULL;
};

ULeapGesture::ULeapGesture(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateGesture())
{
}

ULeapGesture::~ULeapGesture()
{
	delete Private;
}

void ULeapGesture::CleanupRootReferences()
{
	Private->Cleanup();
}

ULeapFrame* ULeapGesture::Frame()
{
	if (Private->Frame == NULL)
	{
		Private->Frame = NewObject<ULeapFrame>(this);
		Private->Frame->SetFlags(RF_RootSet);
	}
	Private->Frame->SetFrame(Private->Gesture.frame());
	return (Private->Frame);
}

ULeapHandList* ULeapGesture::Hands()
{
	if (Private->Hands == NULL)
	{
		Private->Hands = NewObject<ULeapHandList>(this);
		Private->Hands->SetFlags(RF_RootSet);
	}
	Private->Hands->SetHandList(Private->Gesture.hands());
	return (Private->Hands);
}

ULeapPointableList* ULeapGesture::Pointables()
{
	if (Private->Pointables == NULL)
	{
		Private->Pointables = NewObject<ULeapPointableList>(this);
		Private->Pointables->SetFlags(RF_RootSet);
	}
	Private->Pointables->SetPointableList(Private->Gesture.pointables());
	return (Private->Pointables);
}

LeapGestureState gestureState(Leap::Gesture::State State)
{
	switch (State)
	{
	case Leap::Gesture::STATE_START:
		return (GESTURE_STATE_START);
	case Leap::Gesture::STATE_UPDATE:
		return (GESTURE_STATE_UPDATE);
	case Leap::Gesture::STATE_STOP:
		return (GESTURE_STATE_STOP);
	default:
		return (GESTURE_STATE_INVALID);
	}
}

LeapGestureType gestureType(Leap::Gesture::Type Type)
{
	switch (Type)
	{
	case Leap::Gesture::TYPE_CIRCLE:
		return (GESTURE_TYPE_CIRCLE);
	case Leap::Gesture::TYPE_KEY_TAP:
		return (GESTURE_TYPE_KEY_TAP);
	case Leap::Gesture::TYPE_SCREEN_TAP:
		return (GESTURE_TYPE_SCREEN_TAP);
	case Leap::Gesture::TYPE_SWIPE:
		return (GESTURE_TYPE_SWIPE);
	default:
		return (GESTURE_TYPE_INVALID);
	}
}

void ULeapGesture::SetGesture(const Leap::Gesture &Gesture)
{
	Private->Gesture = Gesture;

	Duration = Private->Gesture.duration();
	DurationSeconds = Private->Gesture.durationSeconds();
	Id = Private->Gesture.id();
	IsValid = Private->Gesture.isValid();
	State = gestureState(Private->Gesture.state());
	Type = gestureType(Private->Gesture.type());
}
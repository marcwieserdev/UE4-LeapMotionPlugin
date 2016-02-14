#include "LeapMotionPrivatePCH.h"
#include "LeapTool.h"

class PrivateLeapFrame
{
public:

	~PrivateLeapFrame()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		if (Finger)
		{
			Finger->CleanupRootReferences();
		}
		if (Fingers)
		{
			Fingers->CleanupRootReferences();
		}
		if (Gesture)
		{
			Gesture->CleanupRootReferences();
		}
		if (Gestures)
		{
			Gestures->CleanupRootReferences();
		}
		if (Hand)
		{
			Hand->CleanupRootReferences();
		}
		if (Hands)
		{
			Hands->CleanupRootReferences();
		}
		if (Images)
		{
			Images->CleanupRootReferences();
		}
		if (InteractionBox)
		{
			InteractionBox->CleanupRootReferences();
		}
		if (Pointable)
		{
			Pointable->CleanupRootReferences();
		}
		if (Pointables)
		{
			Pointables->CleanupRootReferences();
		}
		if (Tool)
		{
			Tool->CleanupRootReferences();
		}
		if (Tools)
		{
			Tools->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::Frame Frame;

	ULeapFinger* Finger = NULL;
	ULeapFingerList* Fingers = NULL;

	ULeapGesture* Gesture = NULL;
	ULeapGestureList* Gestures = NULL;

	ULeapHand* Hand = NULL;
	ULeapHandList* Hands = NULL;

	ULeapImageList* Images = NULL;
	ULeapInteractionBox* InteractionBox = NULL;

	ULeapPointable* Pointable = NULL;
	ULeapPointableList* Pointables = NULL;

	ULeapTool* Tool = NULL;
	ULeapToolList* Tools = NULL;
};

ULeapFrame::ULeapFrame(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateLeapFrame())
{
}

ULeapFrame::~ULeapFrame()
{
	delete Private;
}

void ULeapFrame::CleanupRootReferences()
{
	Private->Cleanup();
	if (this->HasAnyFlags(RF_RootSet))
	{
		this->RemoveFromRoot();
	}
}

ULeapFinger* ULeapFrame::Finger(int32 Id)
{
	if (Private->Finger == NULL)
	{
		Private->Finger = NewObject<ULeapFinger>(this);
		Private->Finger->SetFlags(RF_RootSet);
	}
	Private->Finger->SetFinger(Private->Frame.finger(Id));
	return Private->Finger;
}

ULeapFingerList* ULeapFrame::Fingers()
{
	if (Private->Fingers == NULL)
	{
		Private->Fingers = NewObject<ULeapFingerList>(this);
		Private->Fingers->SetFlags(RF_RootSet);
	}
	Private->Fingers->SetFingerList(Private->Frame.fingers());
	return (Private->Fingers);
}

ULeapGesture* ULeapFrame::Gesture(int32 id)
{
	if (Private->Gesture == NULL)
	{
		Private->Gesture = NewObject<ULeapGesture>(this);
		Private->Gesture->SetFlags(RF_RootSet);
	}
	Private->Gesture->SetGesture(Private->Frame.gesture(id));
	return Private->Gesture;
}

ULeapGestureList* ULeapFrame::Gestures()
{
	if (Private->Gestures == NULL)
	{
		Private->Gestures = NewObject<ULeapGestureList>(this);
		Private->Gestures->SetFlags(RF_RootSet);
	}
	Private->Gestures->SetGestureList(Private->Frame.gestures());
	return (Private->Gestures);
}

ULeapGestureList* ULeapFrame::GesturesSinceFrame(class ULeapFrame* Frame)
{
	if (Private->Gestures == NULL)
	{
		Private->Gestures = NewObject<ULeapGestureList>(this);
		Private->Gestures->SetFlags(RF_RootSet);
	}
	Private->Gestures->SetGestureList(Private->Frame.gestures(Frame->GetFrame()));
	return (Private->Gestures);
}

ULeapHand* ULeapFrame::Hand(int32 Id)
{
	if (Private->Hand == NULL)
	{
		Private->Hand = NewObject<ULeapHand>(this);
		Private->Hand->SetFlags(RF_RootSet);
	}
	Private->Hand->SetHand(Private->Frame.hand(Id));
	return Private->Hand;
}

ULeapHandList* ULeapFrame::Hands()
{
	if (Private->Hands == NULL)
	{
		Private->Hands = NewObject<ULeapHandList>(this);
		Private->Hands->SetFlags(RF_RootSet);
	}
	Private->Hands->SetHandList(Private->Frame.hands());
	return (Private->Hands);
}


ULeapImageList* ULeapFrame::Images()
{
	if (Private->Images == NULL)
	{
		Private->Images = NewObject<ULeapImageList>(this);
		Private->Images->SetFlags(RF_RootSet);
	}
	Private->Images->SetLeapImageList(Private->Frame.images());
	return (Private->Images);
}

ULeapInteractionBox* ULeapFrame::InteractionBox()
{
	if (Private->InteractionBox == NULL)
	{
		Private->InteractionBox = NewObject<ULeapInteractionBox>(this);
		Private->InteractionBox->SetFlags(RF_RootSet);
	}
	Private->InteractionBox->SetInteractionBox(Private->Frame.interactionBox());
	return (Private->InteractionBox);
}

ULeapPointable* ULeapFrame::Pointable(int32 Id)
{
	if (Private->Pointable == NULL)
	{
		Private->Pointable = NewObject<ULeapPointable>(this);
		Private->Pointable->SetFlags(RF_RootSet);
	}
	Private->Pointable->SetPointable(Private->Frame.pointable(Id));
	return Private->Pointable;
}

ULeapPointableList* ULeapFrame::Pointables()
{
	if (Private->Pointables == NULL)
	{
		Private->Pointables = NewObject<ULeapPointableList>(this);
		Private->Pointables->SetFlags(RF_RootSet);
	}
	Private->Pointables->SetPointableList(Private->Frame.pointables());
	return (Private->Pointables);
}

float ULeapFrame::RotationAngle(class ULeapFrame* Frame)
{
	return Private->Frame.rotationAngle(Frame->GetFrame());
}

float ULeapFrame::RotationAngleAroundAxis(class ULeapFrame* Frame, FVector Axis)
{
	return Private->Frame.rotationAngle(Frame->GetFrame(), ConvertUEToLeap(Axis));
}

FVector ULeapFrame::RotationAxis(class ULeapFrame* Frame)
{
	return ConvertLeapToUE(Private->Frame.rotationAxis(Frame->GetFrame()));
}

float ULeapFrame::RotationProbability(class ULeapFrame* Frame)
{
	return Private->Frame.rotationProbability(Frame->GetFrame());
}

float ULeapFrame::ScaleFactor(class ULeapFrame* Frame)
{
	return Private->Frame.scaleFactor(Frame->GetFrame());
}

float ULeapFrame::ScaleProbability(class ULeapFrame* Frame)
{
	return Private->Frame.scaleProbability(Frame->GetFrame());
}

ULeapTool* ULeapFrame::Tool(int32 Id)
{
	if (Private->Tool == NULL)
	{
		Private->Tool = NewObject<ULeapTool>(this);
		Private->Tool->SetFlags(RF_RootSet);
	}
	Private->Tool->SetTool(Private->Frame.tool(Id));
	return Private->Tool;
}

ULeapToolList* ULeapFrame::Tools()
{
	if (Private->Tools == NULL)
	{
		Private->Tools = NewObject<ULeapToolList>(this);
		Private->Tools->SetFlags(RF_RootSet);
	}
	Private->Tools->SetToolList(Private->Frame.tools());
	return (Private->Tools);
}

FVector ULeapFrame::Translation(class ULeapFrame* Frame)
{
	return ConvertLeapToUE(Private->Frame.translation(Frame->GetFrame()));
}

float ULeapFrame::TranslationProbability(class ULeapFrame* Frame)
{
	return Private->Frame.translationProbability(Frame->GetFrame());
}

const Leap::Frame &ULeapFrame::GetFrame() const
{
	return (Private->Frame);
}

void ULeapFrame::SetFrame(Leap::Controller &Leap, int History)
{
	Leap::Frame frame = Leap.frame(History);

	this->SetFrame(frame);
}

void ULeapFrame::SetFrame(const Leap::Frame &Frame)
{
	Private->Frame = Frame;
	IsValid = Private->Frame.isValid();
	CurrentFPS = Private->Frame.currentFramesPerSecond();
}


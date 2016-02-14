#include "LeapMotionPrivatePCH.h"
#include "LeapSwipeGesture.h"

class PrivateSwipeGesture
{
public:
	~PrivateSwipeGesture()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		if (Pointable)
		{
			Pointable->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::SwipeGesture Gesture;
	ULeapPointable* Pointable = NULL;
};

ULeapSwipeGesture::ULeapSwipeGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateSwipeGesture())
{
}

ULeapSwipeGesture::~ULeapSwipeGesture()
{
	delete Private;
}
void ULeapSwipeGesture::CleanupRootReferences()
{
	ULeapGesture::CleanupRootReferences();
	Private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointable* ULeapSwipeGesture::Pointable()
{
	if (Private->Pointable == NULL)
	{
		Private->Pointable = NewObject<ULeapPointable>(this);
		Private->Pointable->SetFlags(RF_RootSet);
	}
	Private->Pointable->SetPointable(Private->Gesture.pointable());
	return (Private->Pointable);
}

void ULeapSwipeGesture::SetGesture(const Leap::SwipeGesture &Gesture)
{
	//Super
	ULeapGesture::SetGesture(Gesture);

	Private->Gesture = Gesture;

	Direction = ConvertLeapToUE(Private->Gesture.direction());
	Position = ConvertAndScaleLeapToUE(Private->Gesture.position());
	Speed = ScaleLeapToUE(Private->Gesture.speed());
	StartPosition = ConvertAndScaleLeapToUE(Private->Gesture.startPosition());

	//Convenience
	BasicDirection = LeapBasicVectorDirection(Direction);
}
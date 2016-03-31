#include "LeapMotionPrivatePCH.h"
#include "LeapSwipeGesture.h"

class PrivateSwipeGesture
{
public:
	Leap::SwipeGesture Gesture;
	ULeapPointable* PPointable = nullptr;
};

ULeapSwipeGesture::ULeapSwipeGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateSwipeGesture())
{
}

ULeapSwipeGesture::~ULeapSwipeGesture()
{
	delete Private;
}

ULeapPointable* ULeapSwipeGesture::Pointable()
{
	if (PPointable == nullptr)
	{
		PPointable = NewObject<ULeapPointable>(this);
	}
	PPointable->SetPointable(Private->Gesture.pointable());
	return (PPointable);
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
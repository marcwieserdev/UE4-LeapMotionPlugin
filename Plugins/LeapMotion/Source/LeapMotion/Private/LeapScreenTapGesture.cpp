#include "LeapMotionPrivatePCH.h"
#include "LeapScreenTapGesture.h"

class PrivateScreenTapGesture
{
public:
	Leap::ScreenTapGesture Gesture;
};

ULeapScreenTapGesture::ULeapScreenTapGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateScreenTapGesture())
{
}

ULeapScreenTapGesture::~ULeapScreenTapGesture()
{
	delete Private;
}

ULeapPointable* ULeapScreenTapGesture::Pointable()
{
	if (PPointable == nullptr)
	{
		PPointable = NewObject<ULeapPointable>(this);
	}
	PPointable->SetPointable(Private->Gesture.pointable());
	return (PPointable);
}
void ULeapScreenTapGesture::SetGesture(const Leap::ScreenTapGesture &Gesture)
{
	//Super
	ULeapGesture::SetGesture(Gesture);

	Private->Gesture = Gesture;

	Direction = ConvertLeapToUE(Private->Gesture.direction());
	Position = ConvertAndScaleLeapToUE(Private->Gesture.position());
	Progress = Private->Gesture.progress();

	//Convenience
	BasicDirection = LeapBasicVectorDirection(Direction);
}
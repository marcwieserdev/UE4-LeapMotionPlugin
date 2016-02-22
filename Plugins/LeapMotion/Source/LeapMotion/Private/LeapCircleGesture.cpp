#include "LeapMotionPrivatePCH.h"
#include "LeapCircleGesture.h"
#include "LeapGesture.h"
#include "Math.h"

class PrivateCircleGesture
{
public:
	~PrivateCircleGesture()
	{
	}
	Leap::CircleGesture Gesture;
};

ULeapCircleGesture::ULeapCircleGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateCircleGesture)
{
}

ULeapCircleGesture::~ULeapCircleGesture()
{
	delete Private;
}

ULeapPointable* ULeapCircleGesture::Pointable()
{
	if (PPointable == nullptr)
	{
		PPointable = NewObject<ULeapPointable>(this);
	}
	PPointable->SetPointable(Private->Gesture.pointable());
	return (PPointable);
}

void ULeapCircleGesture::SetGesture(const Leap::CircleGesture &Gesture)
{
	//Super
	ULeapGesture::SetGesture(Gesture);

	Private->Gesture = Gesture;

	Center = ConvertAndScaleLeapToUE(Private->Gesture.center());
	Normal = ConvertLeapToUE(Private->Gesture.normal());
	Progress = Private->Gesture.progress();
	Radius = ScaleLeapToUE(Private->Gesture.radius());	//scale
}
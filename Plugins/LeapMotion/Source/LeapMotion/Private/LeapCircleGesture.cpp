#include "LeapMotionPrivatePCH.h"
#include "LeapCircleGesture.h"
#include "LeapGesture.h"
#include "Math.h"

class PrivateCircleGesture
{
public:
	~PrivateCircleGesture()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		/*if (Pointable)
		{
			Pointable->CleanupRootReferences();
		}
		CleanupCalled = true;*/
	}
	bool CleanupCalled = false;
	Leap::CircleGesture Gesture;
	ULeapPointable* Pointable = NULL;
};

ULeapCircleGesture::ULeapCircleGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateCircleGesture)
{
}

ULeapCircleGesture::~ULeapCircleGesture()
{
	delete Private;
}

void ULeapCircleGesture::CleanupRootReferences()
{
	/*ULeapGesture::CleanupRootReferences();
	Private->Cleanup();
	this->RemoveFromRoot();*/
}

ULeapPointable* ULeapCircleGesture::Pointable()
{
	if (Private->Pointable == NULL)
	{
		Private->Pointable = NewObject<ULeapPointable>(this);
		Private->Pointable->SetFlags(RF_ClassDefaultObject);
	}
	Private->Pointable->SetPointable(Private->Gesture.pointable());
	return (Private->Pointable);
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
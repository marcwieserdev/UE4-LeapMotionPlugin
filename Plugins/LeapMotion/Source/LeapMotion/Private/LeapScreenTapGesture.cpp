#include "LeapMotionPrivatePCH.h"
#include "LeapScreenTapGesture.h"

class PrivateScreenTapGesture
{
public:
	~PrivateScreenTapGesture()
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
		}*/
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::ScreenTapGesture Gesture;
	ULeapPointable* Pointable = NULL;
};

ULeapScreenTapGesture::ULeapScreenTapGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateScreenTapGesture())
{
}

ULeapScreenTapGesture::~ULeapScreenTapGesture()
{
	delete Private;
}
void ULeapScreenTapGesture::CleanupRootReferences()
{
	//ULeapGesture::CleanupRootReferences();
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapPointable* ULeapScreenTapGesture::Pointable()
{
	if (Private->Pointable == NULL)
	{
		Private->Pointable = NewObject<ULeapPointable>(this);
		Private->Pointable->SetFlags(RF_ClassDefaultObject);
	}
	Private->Pointable->SetPointable(Private->Gesture.pointable());
	return (Private->Pointable);
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
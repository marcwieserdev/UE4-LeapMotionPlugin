#include "LeapMotionPrivatePCH.h"
#include "LeapKeyTapGesture.h"

class PrivateKeyTapGesture
{
public:
	~PrivateKeyTapGesture()
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
	Leap::KeyTapGesture Gesture;
	ULeapPointable* Pointable = NULL;
};

ULeapKeyTapGesture::ULeapKeyTapGesture(const FObjectInitializer &ObjectInitializer) : ULeapGesture(ObjectInitializer), Private(new PrivateKeyTapGesture())
{
}

ULeapKeyTapGesture::~ULeapKeyTapGesture()
{
	delete Private;
}
void ULeapKeyTapGesture::CleanupRootReferences()
{
	//ULeapGesture::CleanupRootReferences();
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapPointable* ULeapKeyTapGesture::Pointable()
{
	if (Private->Pointable == NULL)
	{
		Private->Pointable = NewObject<ULeapPointable>(this);
		Private->Pointable->SetFlags(RF_ClassDefaultObject);
	}
	Private->Pointable->SetPointable(Private->Gesture.pointable());
	return (Private->Pointable);
}

void ULeapKeyTapGesture::SetGesture(const Leap::KeyTapGesture &Gesture)
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
#include "LeapMotionPrivatePCH.h"
#include "LeapCircleGesture.h"
#include "LeapGesture.h"
#include "Math.h"

class PrivateCircleGesture
{
public:
	~PrivateCircleGesture()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (pointable)
			pointable->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::CircleGesture gesture;
	ULeapPointable* pointable = NULL;
};

ULeapCircleGesture::ULeapCircleGesture(const FObjectInitializer &init) : ULeapGesture(init), _private(new PrivateCircleGesture)
{
}

ULeapCircleGesture::~ULeapCircleGesture()
{
	delete _private;
}

void ULeapCircleGesture::CleanupRootReferences()
{
	ULeapGesture::CleanupRootReferences();
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointable* ULeapCircleGesture::Pointable()
{
	if (_private->pointable == NULL)
	{
		_private->pointable = NewObject<ULeapPointable>(this);
		_private->pointable->SetFlags(RF_RootSet);
	}
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void ULeapCircleGesture::setGesture(const Leap::CircleGesture &Gesture)
{
	//Super
	ULeapGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Center = convertAndScaleLeapToUE(_private->gesture.center());
	Normal = convertLeapToUE(_private->gesture.normal());
	Progress = _private->gesture.progress();
	Radius = scaleLeapToUE(_private->gesture.radius());	//scale
}
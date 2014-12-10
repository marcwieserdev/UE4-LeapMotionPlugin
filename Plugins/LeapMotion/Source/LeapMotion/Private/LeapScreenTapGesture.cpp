#include "LeapMotionPrivatePCH.h"
#include "LeapScreenTapGesture.h"

class PrivateScreenTapGesture
{
public:
	~PrivateScreenTapGesture()
	{
		if(!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (pointable)
			pointable->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::ScreenTapGesture gesture;
	ULeapPointable* pointable = NULL;
};

ULeapScreenTapGesture::ULeapScreenTapGesture(const FObjectInitializer &init) : ULeapGesture(init), _private(new PrivateScreenTapGesture())
{
}

ULeapScreenTapGesture::~ULeapScreenTapGesture()
{
	delete _private;
}
void ULeapScreenTapGesture::CleanupRootReferences()
{
	ULeapGesture::CleanupRootReferences();
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointable* ULeapScreenTapGesture::Pointable()
{
	if (_private->pointable == NULL)
	{
		_private->pointable = NewObject<ULeapPointable>(this);
		_private->pointable->SetFlags(RF_RootSet);
	}
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}
void ULeapScreenTapGesture::setGesture(const Leap::ScreenTapGesture &Gesture)
{
	//Super
	ULeapGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Direction = convertLeapToUE(_private->gesture.direction());
	Position = convertAndScaleLeapToUE(_private->gesture.position());
	Progress = _private->gesture.progress();

	//Convenience
	BasicDirection = basicDirection(Direction);
}
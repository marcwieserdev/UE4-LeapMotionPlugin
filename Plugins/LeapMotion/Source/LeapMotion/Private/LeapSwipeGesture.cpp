#include "LeapMotionPrivatePCH.h"
#include "LeapSwipeGesture.h"

class PrivateSwipeGesture
{
public:
	~PrivateSwipeGesture()
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
	Leap::SwipeGesture gesture;
	ULeapPointable* pointable = NULL;
};

ULeapSwipeGesture::ULeapSwipeGesture(const FObjectInitializer &init) : ULeapGesture(init), _private(new PrivateSwipeGesture())
{
}

ULeapSwipeGesture::~ULeapSwipeGesture()
{
	delete _private;
}
void ULeapSwipeGesture::CleanupRootReferences()
{
	ULeapGesture::CleanupRootReferences();
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointable* ULeapSwipeGesture::Pointable()
{
	if (_private->pointable == NULL)
	{
		_private->pointable = NewObject<ULeapPointable>(this);
		_private->pointable->SetFlags(RF_RootSet);
	}
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void ULeapSwipeGesture::setGesture(const Leap::SwipeGesture &Gesture)
{
	//Super
	ULeapGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Direction = convertLeapToUE(_private->gesture.direction());
	Position = convertAndScaleLeapToUE(_private->gesture.position());
	Speed = scaleLeapToUE(_private->gesture.speed());
	StartPosition = convertAndScaleLeapToUE(_private->gesture.startPosition());

	//Convenience
	BasicDirection = basicDirection(Direction);
}
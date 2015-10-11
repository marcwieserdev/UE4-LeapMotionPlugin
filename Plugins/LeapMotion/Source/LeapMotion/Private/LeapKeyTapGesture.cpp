#include "LeapMotionPrivatePCH.h"
#include "LeapKeyTapGesture.h"

class PrivateKeyTapGesture
{
public:
	~PrivateKeyTapGesture()
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
	Leap::KeyTapGesture gesture;
	ULeapPointable* pointable = NULL;
};

ULeapKeyTapGesture::ULeapKeyTapGesture(const FObjectInitializer &init) : ULeapGesture(init), _private(new PrivateKeyTapGesture())
{
}

ULeapKeyTapGesture::~ULeapKeyTapGesture()
{
	delete _private;
}
void ULeapKeyTapGesture::CleanupRootReferences()
{
	ULeapGesture::CleanupRootReferences();
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointable* ULeapKeyTapGesture::Pointable()
{
	if (_private->pointable == NULL)
	{
		_private->pointable = NewObject<ULeapPointable>(this);
		_private->pointable->SetFlags(RF_RootSet);
	}
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void ULeapKeyTapGesture::setGesture(const Leap::KeyTapGesture &Gesture)
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
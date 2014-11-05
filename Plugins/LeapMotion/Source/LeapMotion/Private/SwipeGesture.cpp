#include "LeapMotionPrivatePCH.h"
#include "SwipeGesture.h"

class PrivateSwipeGesture
{
public:
	Leap::SwipeGesture gesture;
	UPointable* pointable = NULL;
};

USwipeGesture::USwipeGesture(const FPostConstructInitializeProperties &init) : UGesture(init), _private(new PrivateSwipeGesture())
{
}

USwipeGesture::~USwipeGesture()
{
	delete _private;
}


UPointable* USwipeGesture::Pointable()
{
	if (_private->pointable == NULL)
		_private->pointable = NewObject<UPointable>(this);
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void USwipeGesture::setGesture(const Leap::SwipeGesture &Gesture)
{
	//Super
	UGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Direction = convertLeapToUE(_private->gesture.direction());
	Position = convertAndScaleLeapToUE(_private->gesture.position());
	Speed = scaleLeapToUE(_private->gesture.speed());
	StartPosition = convertAndScaleLeapToUE(_private->gesture.startPosition());

	//Convenience
	CardinalDirection = cardinalDirection(Direction);
}
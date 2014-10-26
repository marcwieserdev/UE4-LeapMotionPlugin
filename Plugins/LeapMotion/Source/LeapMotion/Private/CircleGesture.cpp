#include "LeapMotionPrivatePCH.h"
#include "CircleGesture.h"
#include "Gesture.h"
#include "Math.h"

class PrivateCircleGesture
{
public:
	Leap::CircleGesture gesture;
	UPointable* pointable = NULL;
};

UCircleGesture::UCircleGesture(const FPostConstructInitializeProperties &init) : UGesture(init), _private(new PrivateCircleGesture)
{
}

UCircleGesture::~UCircleGesture()
{
	delete _private;
}

UPointable* UCircleGesture::Pointable()
{
	if (_private->pointable == NULL)
		_private->pointable = NewObject<UPointable>(this);
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void UCircleGesture::setGesture(const Leap::CircleGesture &Gesture)
{
	//Super
	UGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Center = convertAndScaleLeapToUE(_private->gesture.center());
	Normal = convertLeapToUE(_private->gesture.normal());
	Progress = _private->gesture.progress();
	Radius = scaleLeapToUE(_private->gesture.radius());	//scale
}
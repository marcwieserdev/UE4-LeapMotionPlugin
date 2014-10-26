#include "LeapMotionPrivatePCH.h"
#include "ScreenTapGesture.h"

class PrivateScreenTapGesture
{
public:
	Leap::ScreenTapGesture gesture;
	UPointable* pointable = NULL;
};

UScreenTapGesture::UScreenTapGesture(const FPostConstructInitializeProperties &init) : UGesture(init), _private(new PrivateScreenTapGesture())
{
}

UScreenTapGesture::~UScreenTapGesture()
{
	delete _private;
}

UPointable* UScreenTapGesture::Pointable()
{
	if (_private->pointable == NULL)
		_private->pointable = NewObject<UPointable>(this);
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}
void UScreenTapGesture::setGesture(const Leap::ScreenTapGesture &Gesture)
{
	//Super
	UGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Direction = convertLeapToUE(_private->gesture.direction());
	Position = convertAndScaleLeapToUE(_private->gesture.position());
	Progress = _private->gesture.progress();
}
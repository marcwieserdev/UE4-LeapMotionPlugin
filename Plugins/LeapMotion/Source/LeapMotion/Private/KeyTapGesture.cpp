#include "LeapMotionPrivatePCH.h"
#include "KeyTapGesture.h"

class PrivateKeyTapGesture
{
public:
	Leap::KeyTapGesture gesture;
	UPointable* pointable = NULL;
};

UKeyTapGesture::UKeyTapGesture(const FPostConstructInitializeProperties &init) : UGesture(init), _private(new PrivateKeyTapGesture())
{
}

UKeyTapGesture::~UKeyTapGesture()
{
	delete _private;
}

UPointable* UKeyTapGesture::Pointable()
{
	if (_private->pointable == NULL)
		_private->pointable = NewObject<UPointable>(this);
	_private->pointable->setPointable(_private->gesture.pointable());
	return (_private->pointable);
}

void UKeyTapGesture::setGesture(const Leap::KeyTapGesture &Gesture)
{
	//Super
	UGesture::setGesture(Gesture);

	_private->gesture = Gesture;

	Direction = convertLeapToUE(_private->gesture.direction());
	Position = convertAndScaleLeapToUE(_private->gesture.position());
	Progress = _private->gesture.progress();
}
#include "LeapMotionPrivatePCH.h"

class PrivateGesture
{
public:
	Leap::Gesture gesture;
	ULeapFrame* frame = NULL;
	UHandList* hands = NULL;
	UPointableList* pointables = NULL;
};

UGesture::UGesture(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateGesture())
{
}

UGesture::~UGesture()
{
	delete _private;
}

ULeapFrame* UGesture::Frame()
{
	if (_private->frame == NULL)
		_private->frame = NewObject<ULeapFrame>(this);
	_private->frame->setFrame(_private->gesture.frame());
	return (_private->frame);
}

UHandList* UGesture::Hands()
{
	if (_private->hands == NULL)
		_private->hands = NewObject<UHandList>(this);
	_private->hands->setHandList(_private->gesture.hands());
	return (_private->hands);
}

UPointableList* UGesture::Pointables()
{
	if (_private->pointables == NULL)
		_private->pointables = NewObject<UPointableList>(this);
	_private->pointables->setPointableList(_private->gesture.pointables());
	return (_private->pointables);
}

LeapGestureState gestureState(Leap::Gesture::State state)
{
	switch (state)
	{
	case Leap::Gesture::STATE_START:
		return (GESTURE_STATE_START);
	case Leap::Gesture::STATE_UPDATE:
		return (GESTURE_STATE_UPDATE);
	case Leap::Gesture::STATE_STOP:
		return (GESTURE_STATE_STOP);
	default:
		return (GESTURE_STATE_INVALID);
	}
}

LeapGestureType gestureType(Leap::Gesture::Type type)
{
	switch (type)
	{
	case Leap::Gesture::TYPE_CIRCLE:
		return (GESTURE_TYPE_CIRCLE);
	case Leap::Gesture::TYPE_KEY_TAP:
		return (GESTURE_TYPE_KEY_TAP);
	case Leap::Gesture::TYPE_SCREEN_TAP:
		return (GESTURE_TYPE_SCREEN_TAP);
	case Leap::Gesture::TYPE_SWIPE:
		return (GESTURE_TYPE_SWIPE);
	default:
		return (GESTURE_TYPE_INVALID);
	}
}

void UGesture::setGesture(const Leap::Gesture &Gesture)
{
	_private->gesture = Gesture;

	Duration = _private->gesture.duration();
	DurationSeconds = _private->gesture.durationSeconds();
	Id = _private->gesture.id();
	IsValid = _private->gesture.isValid();
	State = gestureState(_private->gesture.state());
	Type = gestureType(_private->gesture.type());
}
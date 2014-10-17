#include "LeapMotionPrivatePCH.h"

UGesture::UGesture(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UGesture::~UGesture()
{
}

ULeapFrame* UGesture::Frame()
{
	ULeapFrame *frame;

	frame = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	frame->setFrame(_gesture.frame());
	return (frame);
}

UHandList* UGesture::Hands()
{
	UHandList *hands;

	hands = ConstructObject<UHandList>(UHandList::StaticClass());
	hands->setHandList(_gesture.hands());
	return (hands);
}

UPointableList* UGesture::Pointables()
{
	UPointableList *pointables;

	pointables = ConstructObject<UPointableList>(UPointableList::StaticClass());
	pointables->setPointableList(_gesture.pointables());
	return (pointables);
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
	_gesture = Gesture;

	Duration = _gesture.duration();
	DurationSeconds = _gesture.durationSeconds();
	Id = _gesture.id();
	IsValid = _gesture.isValid();
	State = gestureState(_gesture.state());
	Type = gestureType(_gesture.type());
}
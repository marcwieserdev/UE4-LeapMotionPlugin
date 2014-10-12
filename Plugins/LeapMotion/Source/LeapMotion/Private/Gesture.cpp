#include "LeapMotionPrivatePCH.h"

UGesture::UGesture(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UGesture::~UGesture()
{
}

float UGesture::Duration() const
{
	return _gesture.duration();
}

float UGesture::DurationSeconds() const
{
	return _gesture.durationSeconds();
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

int32 UGesture::Id()
{
	return _gesture.id();
}

bool UGesture::IsValid() const
{
	return _gesture.isValid();
}

UPointableList* UGesture::Pointables()
{
	UPointableList *pointables;

	pointables = ConstructObject<UPointableList>(UPointableList::StaticClass());
	pointables->setPointableList(_gesture.pointables());
	return (pointables);
}

LeapGestureState UGesture::State()
{
	switch (_gesture.state())
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

LeapGestureType UGesture::Type()
{
	switch (_gesture.type())
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
}
#include "LeapMotionPrivatePCH.h"

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapFrame::~ULeapFrame()
{
}

UHandList* ULeapFrame::Hands()
{
	if (!_hands)
		_hands = NewObject<UHandList>(this);
	_hands->setHandList(_frame.hands());
	return (_hands);
}

UFingerList* ULeapFrame::Fingers()
{
	if (!_fingers)
		_fingers = NewObject<UFingerList>(this);
	_fingers->setFingerList(_frame.fingers());
	return (_fingers);
}

UGestureList* ULeapFrame::Gestures()
{
	if (!_gestures)
		_gestures = NewObject<UGestureList>(this);
	_gestures->setGestureList(_frame.gestures());
	return (_gestures);
}

UInteractionBox* ULeapFrame::InteractionBox()
{
	if (!_interactionBox)
		_interactionBox = NewObject<UInteractionBox>(this);
	_interactionBox->setInteractionBox(_frame.interactionBox());
	return (_interactionBox);
}

UPointableList* ULeapFrame::Pointables()
{
	if (!_pointableList)
		_pointableList = NewObject<UPointableList>(this);
	_pointableList->setPointableList(_frame.pointables());
	return (_pointableList);
}

ULeapImageList* ULeapFrame::Images()
{
	if (!_leapImageList)
		_leapImageList = NewObject<ULeapImageList>(this);
	_leapImageList->setLeapImageList(_frame.images());
	return (_leapImageList);
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	_frame = leap.frame(history);
	IsValid = _frame.isValid();
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_frame = frame;
	IsValid = _frame.isValid();
}

const Leap::Frame &ULeapFrame::getFrame() const
{
	return (_frame);
}
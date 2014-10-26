#include "LeapMotionPrivatePCH.h"

class PrivateLeapFrame
{
public:
	Leap::Frame frame;
	UHandList* hands = NULL;
	UFingerList* fingers = NULL;
	UGestureList* gestures = NULL;
	UInteractionBox* interactionBox = NULL;
	UPointableList* pointables = NULL;
	ULeapImageList* images = NULL;
};

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateLeapFrame())
{
}

ULeapFrame::~ULeapFrame()
{
	delete _private;
}

UHandList* ULeapFrame::Hands()
{
	if (_private->hands == NULL)
		_private->hands = NewObject<UHandList>(this);
	_private->hands->setHandList(_private->frame.hands());
	return (_private->hands);
}

UFingerList* ULeapFrame::Fingers()
{
	if (_private->fingers == NULL)
		_private->fingers = NewObject<UFingerList>(this);
	_private->fingers->setFingerList(_private->frame.fingers());
	return (_private->fingers);
}

UGestureList* ULeapFrame::Gestures()
{
	if (_private->gestures == NULL)
		_private->gestures = NewObject<UGestureList>(this);
	_private->gestures->setGestureList(_private->frame.gestures());
	return (_private->gestures);
}

UInteractionBox* ULeapFrame::InteractionBox()
{
	if (_private->interactionBox == NULL)
		_private->interactionBox = NewObject<UInteractionBox>(this);
	_private->interactionBox->setInteractionBox(_private->frame.interactionBox());
	return (_private->interactionBox);
}

UPointableList* ULeapFrame::Pointables()
{
	if (_private->pointables == NULL)
		_private->pointables = NewObject<UPointableList>(this);
	_private->pointables->setPointableList(_private->frame.pointables());
	return (_private->pointables);
}

ULeapImageList* ULeapFrame::Images()
{
	if (_private->images == NULL)
		_private->images = NewObject<ULeapImageList>(this);
	_private->images->setLeapImageList(_private->frame.images());
	return (_private->images);
}

const Leap::Frame &ULeapFrame::getFrame() const
{
	return (_private->frame);
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	Leap::Frame frame = leap.frame(history);
	_private->frame = frame;
	IsValid = _private->frame.isValid();
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_private->frame = frame;
	IsValid = _private->frame.isValid();
}


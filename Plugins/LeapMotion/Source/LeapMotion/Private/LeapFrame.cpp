#include "LeapMotionPrivatePCH.h"

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapFrame::~ULeapFrame()
{
}

bool ULeapFrame::IsValid() const
{
	return _frame.isValid();
}

UHandList* ULeapFrame::Hands()
{
	UHandList* handlist;

	handlist = ConstructObject<UHandList>(UHandList::StaticClass());
	handlist->setHandList(_frame.hands());
	return (handlist);
}

UFingerList* ULeapFrame::Fingers()
{
	UFingerList* fingerlist;

	fingerlist = ConstructObject<UFingerList>(UFingerList::StaticClass());
	fingerlist->setFingerList(_frame.fingers());
	return (fingerlist);
}

UGestureList* ULeapFrame::Gestures()
{
	UGestureList* gestures;

	gestures = ConstructObject<UGestureList>(UGestureList::StaticClass());
	gestures->setGestureList(_frame.gestures());
	return (gestures);
}

UInteractionBox* ULeapFrame::InteractionBox()
{
	UInteractionBox* box;

	box = ConstructObject<UInteractionBox>(UInteractionBox::StaticClass());
	box->setInteractionBox(_frame.interactionBox());
	return (box);
}

UPointableList* ULeapFrame::Pointables()
{
	UPointableList* pointables;

	pointables = ConstructObject<UPointableList>(UPointableList::StaticClass());
	pointables->setPointableList(_frame.pointables());
	return (pointables);
}

ULeapImageList* ULeapFrame::Images()
{
	ULeapImageList* images;

	images = ConstructObject<ULeapImageList>(ULeapImageList::StaticClass());
	images->setLeapImageList(_frame.images());
	return (images);
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	_frame = leap.frame(history);
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_frame = frame;
}

const Leap::Frame &ULeapFrame::getFrame() const
{
	return (_frame);
}
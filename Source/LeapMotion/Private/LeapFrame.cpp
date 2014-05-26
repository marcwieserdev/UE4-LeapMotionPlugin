#include "LeapMotionPrivatePCH.h"

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapFrame::~ULeapFrame()
{
}

float ULeapFrame::currentFramePerSecond() const
{
	return (_frame.currentFramesPerSecond());
}

bool ULeapFrame::IsValid() const
{
	return _frame.isValid();
}

UHandList *ULeapFrame::hands()
{
	UHandList *handlist;

	handlist = ConstructObject<UHandList>(UHandList::StaticClass());
	handlist->setHandList(_frame.hands());
	return (handlist);
}

UFingerList *ULeapFrame::fingers()
{
	UFingerList *fingerlist;

	fingerlist = ConstructObject<UFingerList>(UFingerList::StaticClass());
	fingerlist->setFingerList(_frame.fingers());
	return (fingerlist);
}

UToolList *ULeapFrame::tools()
{
	UToolList *toollist;

	toollist = ConstructObject<UToolList>(UToolList::StaticClass());
	toollist->setToolList(_frame.tools());
	return (toollist);
}

UPointableList *ULeapFrame::pointables()
{
	UPointableList *pointablelist;

	pointablelist = ConstructObject<UPointableList>(UPointableList::StaticClass());
	pointablelist->setPointableList(_frame.pointables());
	return (pointablelist);
}

int32 ULeapFrame::TimeStamp() const
{
	return (_frame.timestamp());
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
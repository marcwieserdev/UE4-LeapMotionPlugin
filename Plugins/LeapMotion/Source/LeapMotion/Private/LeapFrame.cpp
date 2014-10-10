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

UHandList *ULeapFrame::hands()
{
	UHandList *handlist;

	handlist = ConstructObject<UHandList>(UHandList::StaticClass());
	handlist->setHandList(_frame.hands());
	return (handlist);
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
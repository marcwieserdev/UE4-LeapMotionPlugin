#include "LeapMotionPrivatePCH.h"

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapFrame::~ULeapFrame()
{
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	_frame = leap.frame(history);
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_frame = frame;
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
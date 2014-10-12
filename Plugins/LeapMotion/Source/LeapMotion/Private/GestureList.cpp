#include "LeapMotionPrivatePCH.h"

UGestureList::UGestureList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UGestureList::~UGestureList()
{
}

bool UGestureList::isEmpty() const
{
	return (_gestures.isEmpty());
}

int32 UGestureList::Count()
{
	return (_gestures.count());
}


UGesture* UGestureList::getIndex(int32 index)
{
	UGesture *gesture;

	gesture = ConstructObject<UGesture>(UGesture::StaticClass());
	gesture->setGesture(_gestures[index]);
	return (gesture);
}

UGesture* UGestureList::operator[](int index)
{
	return getIndex(index);
}

void UGestureList::setGestureList(const Leap::GestureList &GestureList)
{
	_gestures = GestureList;
}
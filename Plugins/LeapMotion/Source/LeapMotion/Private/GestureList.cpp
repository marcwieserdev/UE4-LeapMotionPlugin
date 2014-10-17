#include "LeapMotionPrivatePCH.h"

UGestureList::UGestureList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UGestureList::~UGestureList()
{
}

UGesture* UGestureList::getIndex(int32 index)
{
	if (!_gesture)
		_gesture = NewObject<UGesture>(this, UGesture::StaticClass());
	_gesture->setGesture(_gestures[index]);
	return (_gesture);
}

UGesture* UGestureList::operator[](int index)
{
	return getIndex(index);
}

void UGestureList::setGestureList(const Leap::GestureList &GestureList)
{
	_gestures = GestureList;

	Count = _gestures.count();
	IsEmpty = _gestures.isEmpty();
}
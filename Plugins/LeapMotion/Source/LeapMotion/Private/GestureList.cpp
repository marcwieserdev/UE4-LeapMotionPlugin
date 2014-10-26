#include "LeapMotionPrivatePCH.h"

class PrivateGestureList
{
public:
	Leap::GestureList gestures;
	UGesture* gesture = NULL;
};

UGestureList::UGestureList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateGestureList())
{
}

UGestureList::~UGestureList()
{
	delete _private;
}

UGesture* UGestureList::getIndex(int32 index)
{
	if (_private->gesture == NULL)
		_private->gesture = NewObject<UGesture>(this, UGesture::StaticClass());
	_private->gesture->setGesture(_private->gestures[index]);
	return (_private->gesture);
}

UGesture* UGestureList::operator[](int index)
{
	return getIndex(index);
}

void UGestureList::setGestureList(const Leap::GestureList &GestureList)
{
	_private->gestures = GestureList;

	Count = _private->gestures.count();
	IsEmpty = _private->gestures.isEmpty();
}
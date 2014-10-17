#include "LeapMotionPrivatePCH.h"
#include "FingerList.h"
#include "Finger.h"

UFingerList::UFingerList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UFingerList::~UFingerList()
{
}

UFingerList *UFingerList::append(const UFingerList *list)
{
	UFingerList *newlist;

	newlist = NewObject<UFingerList>(this, UFingerList::StaticClass());
	newlist->setFingerList(this->_fingers.append(list->_fingers));
	return (newlist);
}

UFingerList *UFingerList::extended()
{
	UFingerList *newlist;

	newlist = NewObject<UFingerList>(this, UFingerList::StaticClass());
	newlist->setFingerList(_fingers.extended());
	return (newlist);
}

UFinger *UFingerList::leftmost()
{
	if (!_leftmost)
		_leftmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_leftmost->setFinger(_fingers.leftmost());
	return (_leftmost);
}

UFinger *UFingerList::rightmost()
{
	if (!_rightmost)
		_rightmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_rightmost->setFinger(_fingers.rightmost());
	return (_rightmost);
}


UFinger *UFingerList::frontmost()
{
	if (!_frontmost)
		_frontmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_frontmost->setFinger(_fingers.frontmost());
	return (_frontmost);
}

UFinger *UFingerList::getPointableById(int32 id)
{
	if (!_pointableById)
		_pointableById = NewObject<UFinger>(this, UFinger::StaticClass());
	_pointableById->setFinger(_fingers[id]);
	return (_pointableById);
}

void UFingerList::setFingerList(const Leap::FingerList &fingers)
{
	_fingers = fingers;

	Count = _fingers.count();
	IsEmpty = _fingers.isEmpty();
}
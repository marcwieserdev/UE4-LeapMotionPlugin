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

	newlist = ConstructObject<UFingerList>(UFingerList::StaticClass());
	newlist->setFingerList(this->_fingers.append(list->_fingers));
	return (newlist);
}

UFingerList *UFingerList::extended()
{
	UFingerList *newlist;

	newlist = ConstructObject<UFingerList>(UFingerList::StaticClass());
	newlist->setFingerList(_fingers.extended());
	return (newlist);
}

UFinger *UFingerList::leftmost()
{
	UFinger *pointable;

	pointable = ConstructObject<UFinger>(UFinger::StaticClass());
	pointable->setFinger(_fingers.leftmost());
	return (pointable);
}

UFinger *UFingerList::rightmost()
{
	UFinger *pointable;

	pointable = ConstructObject<UFinger>(UFinger::StaticClass());
	pointable->setFinger(_fingers.rightmost());
	return (pointable);
}


UFinger *UFingerList::frontmost()
{
	UFinger *pointable;

	pointable = ConstructObject<UFinger>(UFinger::StaticClass());
	pointable->setFinger(_fingers.frontmost());
	return (pointable);
}

UFinger *UFingerList::getPointableById(int32 id)
{
	UFinger *pointable;

	pointable = ConstructObject<UFinger>(UFinger::StaticClass());
	pointable->setFinger(_fingers[id]);
	return (pointable);
}

void UFingerList::setFingerList(const Leap::FingerList &fingers)
{
	_fingers = fingers;

	Count = _fingers.count();
	IsEmpty = _fingers.isEmpty();
}
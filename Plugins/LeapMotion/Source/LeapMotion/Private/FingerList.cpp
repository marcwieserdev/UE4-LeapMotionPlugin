#include "LeapMotionPrivatePCH.h"
#include "FingerList.h"
#include "Finger.h"

class PrivateFingerList{
public:
	Leap::FingerList fingers;
	UFinger* frontmost = NULL;
	UFinger* leftmost = NULL;
	UFinger* rightmost = NULL;
	UFinger* pointableById = NULL;
};

UFingerList::UFingerList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateFingerList())
{
}

UFingerList::~UFingerList()
{
	delete _private;
}

UFingerList *UFingerList::append(const UFingerList *list)
{
	UFingerList *newlist;

	newlist = NewObject<UFingerList>(this, UFingerList::StaticClass());
	newlist->setFingerList(_private->fingers.append(list->_private->fingers));
	return (newlist);
}

UFingerList *UFingerList::extended()
{
	UFingerList *newlist;

	newlist = NewObject<UFingerList>(this, UFingerList::StaticClass());
	newlist->setFingerList(_private->fingers.extended());
	return (newlist);
}

UFinger *UFingerList::leftmost()
{
	if (_private->leftmost == NULL)
		_private->leftmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_private->leftmost->setFinger(_private->fingers.leftmost());
	return (_private->leftmost);
}

UFinger *UFingerList::rightmost()
{
	if (_private->rightmost == NULL)
		_private->rightmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_private->rightmost->setFinger(_private->fingers.rightmost());
	return (_private->rightmost);
}


UFinger *UFingerList::frontmost()
{
	if (_private->frontmost == NULL)
		_private->frontmost = NewObject<UFinger>(this, UFinger::StaticClass());
	_private->frontmost->setFinger(_private->fingers.frontmost());
	return (_private->frontmost);
}

UFinger *UFingerList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
		_private->pointableById = NewObject<UFinger>(this, UFinger::StaticClass());
	_private->pointableById->setFinger(_private->fingers[id]);
	return (_private->pointableById);
}

void UFingerList::setFingerList(const Leap::FingerList &fingers)
{
	_private->fingers = fingers;

	Count = _private->fingers.count();
	IsEmpty = _private->fingers.isEmpty();
}
#include "LeapMotionPrivatePCH.h"
#include "PointableList.h"
#include "Pointable.h"

UPointableList::UPointableList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UPointableList::~UPointableList()
{
}

UPointableList *UPointableList::append(UPointableList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->_pointables));
	return (newlist);
}

/*UPointableList *UPointableList::appendTools(UToolList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->_tools));
	return (newlist);
}

UPointableList *UPointableList::appendFingers(UFingerList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->getTools()));
	return (newlist);
}*/

UPointableList *UPointableList::extended()
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this);
	newlist->setPointableList(_pointables.extended());
	return (newlist);
}

UPointable *UPointableList::leftmost()
{
	if (!_leftmost)
		_leftmost = NewObject<UPointable>(this);
	_leftmost->setPointable(_pointables.leftmost());
	return (_leftmost);
}

UPointable *UPointableList::rightmost()
{
	if (!_rightmost)
		_rightmost = NewObject<UPointable>(this);
	_rightmost->setPointable(_pointables.rightmost());
	return (_rightmost);
}


UPointable *UPointableList::frontmost()
{
	if (!_frontmost)
		_frontmost = NewObject<UPointable>(this);
	_frontmost->setPointable(_pointables.frontmost());
	return (_frontmost);
}

UPointable *UPointableList::getPointableById(int32 id)
{
	if (!_pointableById)
		_pointableById = NewObject<UPointable>(this);
	_pointableById->setPointable(_pointables[id]);
	return (_pointableById);
}

void UPointableList::setPointableList(const Leap::PointableList &pointables)
{
	_pointables = pointables;
	Count = _pointables.count();
	IsEmpty = _pointables.isEmpty();
}
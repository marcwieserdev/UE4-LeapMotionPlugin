#include "LeapMotionPrivatePCH.h"
#include "PointableList.h"
#include "Pointable.h"

class PrivatePointableList
{
public:
	Leap::PointableList pointables;
	UPointable* leftmost = NULL;
	UPointable* rightmost = NULL;
	UPointable* frontmost = NULL;
	UPointable* pointableById = NULL;
};

UPointableList::UPointableList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivatePointableList())
{
}

UPointableList::~UPointableList()
{
	delete _private;
}

UPointableList *UPointableList::append(UPointableList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(_private->pointables.append(list->_private->pointables));
	return (newlist);
}

/*UPointableList *UPointableList::appendTools(UToolList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(this->_private->pointables.append(list->_tools));
	return (newlist);
}

UPointableList *UPointableList::appendFingers(UFingerList *list)
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this, UPointableList::StaticClass());
	newlist->setPointableList(this->_private->pointables.append(list->getTools()));
	return (newlist);
}*/

UPointableList *UPointableList::extended()
{
	UPointableList *newlist;

	newlist = NewObject<UPointableList>(this);
	newlist->setPointableList(_private->pointables.extended());
	return (newlist);
}

UPointable *UPointableList::leftmost()
{
	if (_private->leftmost == NULL)
		_private->leftmost = NewObject<UPointable>(this);
	_private->leftmost->setPointable(_private->pointables.leftmost());
	return (_private->leftmost);
}

UPointable *UPointableList::rightmost()
{
	if (_private->rightmost == NULL)
		_private->rightmost = NewObject<UPointable>(this);
	_private->rightmost->setPointable(_private->pointables.rightmost());
	return (_private->rightmost);
}


UPointable *UPointableList::frontmost()
{
	if (_private->frontmost == NULL)
		_private->frontmost = NewObject<UPointable>(this);
	_private->frontmost->setPointable(_private->pointables.frontmost());
	return (_private->frontmost);
}

UPointable *UPointableList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
		_private->pointableById = NewObject<UPointable>(this);
	_private->pointableById->setPointable(_private->pointables[id]);
	return (_private->pointableById);
}

void UPointableList::setPointableList(const Leap::PointableList &pointables)
{
	_private->pointables = pointables;
	Count = _private->pointables.count();
	IsEmpty = _private->pointables.isEmpty();
}
#include "LeapMotionPrivatePCH.h"

UPointableList::UPointableList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UPointableList::~UPointableList()
{
}

UPointableList *UPointableList::append(const UPointableList *list)
{
	UPointableList *newlist;

	newlist = ConstructObject<UPointableList>(UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->_pointables));
	return (newlist);
}
/*
UPointableList *UPointableList::appendTools(const UFingerList *list)
{
	UPointableList *newlist;

	newlist = ConstructObject<UPointableList>(UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->getFingers()));
	return (newlist);
}

UPointableList *UPointableList::appendFingers(const UToolsList *list)
{
	UPointableList *newlist;

	newlist = ConstructObject<UPointableList>(UPointableList::StaticClass());
	newlist->setPointableList(this->_pointables.append(list->getTools()));
	return (newlist);
}
*/
int32 UPointableList::Count() const
{
	return (_pointables.count());
}

UPointableList *UPointableList::extended()
{
	UPointableList *newlist;

	newlist = ConstructObject<UPointableList>(UPointableList::StaticClass());
	newlist->setPointableList(_pointables.extended());
	return (newlist);
}

bool UPointableList::isEmpty() const
{
	return (_pointables.isEmpty());
}

UPointable *UPointableList::leftmost()
{
	UPointable *pointable;

	pointable = ConstructObject<UPointable>(UPointable::StaticClass());
	pointable->setPointable(_pointables.leftmost());
	return (pointable);
}

UPointable *UPointableList::rightmost()
{
	UPointable *pointable;

	pointable = ConstructObject<UPointable>(UPointable::StaticClass());
	pointable->setPointable(_pointables.rightmost());
	return (pointable);
}


UPointable *UPointableList::frontmost()
{
	UPointable *pointable;

	pointable = ConstructObject<UPointable>(UPointable::StaticClass());
	pointable->setPointable(_pointables.frontmost());
	return (pointable);
}

UPointable *UPointableList::getPointableById(int32 id)
{
	UPointable *pointable;

	pointable = ConstructObject<UPointable>(UPointable::StaticClass());
	pointable->setPointable(_pointables[id]);
	return (pointable);
}

void UPointableList::setPointableList(const Leap::PointableList &pointables)
{
	_pointables = pointables;
}
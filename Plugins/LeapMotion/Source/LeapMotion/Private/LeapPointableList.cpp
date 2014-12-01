#include "LeapMotionPrivatePCH.h"
#include "LeapPointableList.h"
#include "LeapPointable.h"

class PrivatePointableList
{
public:
	~PrivatePointableList()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (frontmost)
			frontmost->CleanupRootReferences();
		if (leftmost)
			leftmost->CleanupRootReferences();
		if (rightmost)
			rightmost->CleanupRootReferences();
		if (pointableById)
			pointableById->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::PointableList pointables;
	ULeapPointable* leftmost = NULL;
	ULeapPointable* rightmost = NULL;
	ULeapPointable* frontmost = NULL;
	ULeapPointable* pointableById = NULL;
};

ULeapPointableList::ULeapPointableList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivatePointableList())
{
}

ULeapPointableList::~ULeapPointableList()
{
	delete _private;
}
void ULeapPointableList::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapPointableList *ULeapPointableList::append(ULeapPointableList *list)
{
	ULeapPointableList *newlist;

	newlist = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
	newlist->setPointableList(_private->pointables.append(list->_private->pointables));
	return (newlist);
}

/*ULeapPointableList *ULeapPointableList::appendTools(ULeapToolList *list)
{
	ULeapPointableList *newlist;

	newlist = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
	newlist->setPointableList(this->_private->pointables.append(list->_tools));
	return (newlist);
}

ULeapPointableList *ULeapPointableList::appendFingers(ULeapFingerList *list)
{
	ULeapPointableList *newlist;

	newlist = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
	newlist->setPointableList(this->_private->pointables.append(list->getTools()));
	return (newlist);
}*/

ULeapPointableList *ULeapPointableList::extended()
{
	ULeapPointableList *newlist;

	newlist = NewObject<ULeapPointableList>(this);
	newlist->setPointableList(_private->pointables.extended());
	return (newlist);
}

ULeapPointable *ULeapPointableList::leftmost()
{
	if (_private->leftmost == NULL)
	{
		_private->leftmost = NewObject<ULeapPointable>(this);
		_private->leftmost->SetFlags(RF_RootSet);
	}
	_private->leftmost->setPointable(_private->pointables.leftmost());
	return (_private->leftmost);
}

ULeapPointable *ULeapPointableList::rightmost()
{
	if (_private->rightmost == NULL)
	{
		_private->rightmost = NewObject<ULeapPointable>(this);
		_private->rightmost->SetFlags(RF_RootSet);
	}
	_private->rightmost->setPointable(_private->pointables.rightmost());
	return (_private->rightmost);
}


ULeapPointable *ULeapPointableList::frontmost()
{
	if (_private->frontmost == NULL)
	{
		_private->frontmost = NewObject<ULeapPointable>(this);
		_private->frontmost->SetFlags(RF_RootSet);
	}
	_private->frontmost->setPointable(_private->pointables.frontmost());
	return (_private->frontmost);
}

ULeapPointable *ULeapPointableList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
	{
		_private->pointableById = NewObject<ULeapPointable>(this);
		_private->pointableById->SetFlags(RF_RootSet);
	}
	_private->pointableById->setPointable(_private->pointables[id]);
	return (_private->pointableById);
}

void ULeapPointableList::setPointableList(const Leap::PointableList &pointables)
{
	_private->pointables = pointables;
	Count = _private->pointables.count();
	IsEmpty = _private->pointables.isEmpty();
}
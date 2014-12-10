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
		if (appendedList)
			appendedList->CleanupRootReferences();
		if (extendedList)
			extendedList->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::PointableList pointables;
	ULeapPointable* leftmost = NULL;
	ULeapPointable* rightmost = NULL;
	ULeapPointable* frontmost = NULL;
	ULeapPointable* pointableById = NULL;
	ULeapPointableList* appendedList = NULL;
	ULeapPointableList* extendedList = NULL;
};

ULeapPointableList::ULeapPointableList(const FObjectInitializer &init) : UObject(init), _private(new PrivatePointableList())
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
	if (_private->appendedList == NULL)
	{
		_private->appendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		_private->appendedList->SetFlags(RF_RootSet);
	}
	_private->appendedList->setPointableList(_private->pointables.append(list->_private->pointables));
	return (_private->appendedList);
}

ULeapPointableList *ULeapPointableList::appendTools(ULeapToolList *list)
{
	if (_private->appendedList == NULL)
	{
		_private->appendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		_private->appendedList->SetFlags(RF_RootSet);
	}
	_private->appendedList->setPointableList(this->_private->pointables.append(*list->toolList()));
	return (_private->appendedList);
}

ULeapPointableList *ULeapPointableList::appendFingers(ULeapFingerList *list)
{
	if (_private->appendedList == NULL)
	{
		_private->appendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		_private->appendedList->SetFlags(RF_RootSet);
	}
	_private->appendedList->setPointableList(this->_private->pointables.append(*list->fingerList()));
	return (_private->appendedList);
}

ULeapPointableList *ULeapPointableList::extended()
{
	if (_private->extendedList == NULL)
	{
		_private->extendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		_private->extendedList->SetFlags(RF_RootSet);
	}
	_private->extendedList->setPointableList(_private->pointables.extended());
	return (_private->extendedList);
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
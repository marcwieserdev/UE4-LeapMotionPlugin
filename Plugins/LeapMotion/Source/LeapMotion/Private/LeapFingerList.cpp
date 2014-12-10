#include "LeapMotionPrivatePCH.h"
#include "LeapFingerList.h"
#include "LeapFinger.h"

class PrivateFingerList{
public:
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
	~PrivateFingerList()
	{
		if(!cleanupCalled)
			Cleanup();
	}

	bool cleanupCalled = false;
	Leap::FingerList fingers;
	ULeapFinger* frontmost = NULL;
	ULeapFinger* leftmost = NULL;
	ULeapFinger* rightmost = NULL;
	ULeapFinger* pointableById = NULL;
	ULeapFingerList* appendedList = NULL;
	ULeapFingerList* extendedList = NULL;
};

ULeapFingerList::ULeapFingerList(const FObjectInitializer &init) : UObject(init), _private(new PrivateFingerList())
{
}

ULeapFingerList::~ULeapFingerList()
{
	delete _private;
}

void ULeapFingerList::CleanupRootReferences()
{
	_private->Cleanup();
	if (this->HasAnyFlags(RF_RootSet))
		this->RemoveFromRoot();
}

ULeapFingerList *ULeapFingerList::append(const ULeapFingerList *list)
{
	if (_private->appendedList == NULL)
	{
		_private->appendedList = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
		_private->appendedList->SetFlags(RF_RootSet);
	}
	_private->appendedList->setFingerList(_private->fingers.append(list->_private->fingers));
	return (_private->appendedList);
}

ULeapFingerList *ULeapFingerList::extended()
{
	if (_private->extendedList == NULL)
	{
		_private->extendedList = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
		_private->extendedList->SetFlags(RF_RootSet);
	}
	_private->extendedList->setFingerList(_private->fingers.extended());
	return (_private->extendedList);
}

ULeapFinger *ULeapFingerList::leftmost()
{
	if (_private->leftmost == NULL)
	{
		_private->leftmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		_private->leftmost->SetFlags(RF_RootSet);
	}
	_private->leftmost->setFinger(_private->fingers.leftmost());
	return (_private->leftmost);
}

ULeapFinger *ULeapFingerList::rightmost()
{
	if (_private->rightmost == NULL)
	{
		_private->rightmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		_private->rightmost->SetFlags(RF_RootSet);
	}
	_private->rightmost->setFinger(_private->fingers.rightmost());
	return (_private->rightmost);
}


ULeapFinger *ULeapFingerList::frontmost()
{
	if (_private->frontmost == NULL)
	{
		_private->frontmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		_private->frontmost->SetFlags(RF_RootSet);
	}
	_private->frontmost->setFinger(_private->fingers.frontmost());
	return (_private->frontmost);
}

ULeapFinger *ULeapFingerList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
	{
		_private->pointableById = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		//NB: non-temporary so we add it to the rootset and remove it when the object itself gets destroyed. Behaves like a property except allocated only on need.
		//_private->pointableById->SetFlags(RF_DefaultSubObject);	//causes still PIE attachment error
		_private->pointableById->SetFlags(RF_RootSet);
	}
	_private->pointableById->setFinger(_private->fingers[id]);
	return (_private->pointableById);
}

void ULeapFingerList::setFingerList(const Leap::FingerList &fingers)
{
	_private->fingers = fingers;

	Count = _private->fingers.count();
	IsEmpty = _private->fingers.isEmpty();
}

Leap::FingerList* ULeapFingerList::fingerList()
{
	return &(_private->fingers);
}
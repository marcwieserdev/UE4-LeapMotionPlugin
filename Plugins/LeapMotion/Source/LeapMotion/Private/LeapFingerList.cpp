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
		if (pointableById && pointableById->HasAnyFlags(RF_RootSet))
			pointableById->CleanupRootReferences();
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
};

ULeapFingerList::ULeapFingerList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateFingerList())
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
	ULeapFingerList *newlist;

	newlist = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
	newlist->setFingerList(_private->fingers.append(list->_private->fingers));
	return (newlist);
}

ULeapFingerList *ULeapFingerList::extended()
{
	ULeapFingerList *newlist;

	newlist = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
	newlist->setFingerList(_private->fingers.extended());
	return (newlist);
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
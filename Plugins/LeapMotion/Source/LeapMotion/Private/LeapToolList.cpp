#include "LeapMotionPrivatePCH.h"
#include "LeapToolList.h"
#include "LeapTool.h"

class PrivateToolList
{
public:
	~PrivateToolList()
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
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::ToolList tools;
	ULeapTool* leftmost = NULL;
	ULeapTool* rightmost = NULL;
	ULeapTool* frontmost = NULL;
	ULeapTool* pointableById = NULL;
	ULeapToolList* appendedList = NULL;
};


ULeapToolList::ULeapToolList(const FObjectInitializer &init) : UObject(init), _private(new PrivateToolList())
{
}

ULeapToolList::~ULeapToolList()
{
	delete _private;
}
void ULeapToolList::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapToolList *ULeapToolList::append(const ULeapToolList *list)
{
	if (_private->appendedList == NULL)
	{
		_private->appendedList = NewObject<ULeapToolList>(this, ULeapToolList::StaticClass());
		_private->appendedList->SetFlags(RF_RootSet);
	}
	_private->appendedList->setToolList(this->_private->tools.append(list->_private->tools));
	return (_private->appendedList);
}

int32 ULeapToolList::Count() const
{
	return (_private->tools.count());
}

bool ULeapToolList::isEmpty() const
{
	return (_private->tools.isEmpty());
}

ULeapTool* ULeapToolList::leftmost()
{
	if (_private->leftmost == NULL)
	{
		_private->leftmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		_private->leftmost->SetFlags(RF_RootSet);
	}
	_private->leftmost->setTool(_private->tools.leftmost());
	return (_private->leftmost);
}

ULeapTool* ULeapToolList::rightmost()
{
	if (_private->rightmost == NULL)
	{
		_private->rightmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		_private->rightmost->SetFlags(RF_RootSet);
	}
	_private->rightmost->setTool(_private->tools.rightmost());
	return (_private->rightmost);
}


ULeapTool* ULeapToolList::frontmost()
{

	if (_private->frontmost == NULL)
	{
		_private->frontmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		_private->frontmost->SetFlags(RF_RootSet);
	}
	_private->frontmost->setTool(_private->tools.frontmost());
	return (_private->frontmost);
}

ULeapPointable* ULeapToolList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
	{
		_private->pointableById = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		_private->pointableById->SetFlags(RF_RootSet);
	}
	_private->pointableById->setPointable(_private->tools[id]);
	return (_private->pointableById);
}

void ULeapToolList::setToolList(const Leap::ToolList &pointables)
{
	_private->tools = pointables;
}

const Leap::ToolList* ULeapToolList::toolList()
{
	return &(_private->tools);
}
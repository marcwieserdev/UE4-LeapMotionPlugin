#include "LeapMotionPrivatePCH.h"
#include "ToolList.h"
#include "Tool.h"

class PrivateToolList
{
public:
	Leap::ToolList tools;
	UTool* leftmost = NULL;
	UTool* rightmost = NULL;
	UTool* frontmost = NULL;
	UPointable* pointableById = NULL;
};


UToolList::UToolList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateToolList())
{
}

UToolList::~UToolList()
{
	delete _private;
}

UToolList *UToolList::append(const UToolList *list)
{
	UToolList *newlist;

	newlist = NewObject<UToolList>(this, UToolList::StaticClass());
	newlist->setToolList(this->_private->tools.append(list->_private->tools));
	return (newlist);
}

int32 UToolList::Count() const
{
	return (_private->tools.count());
}

bool UToolList::isEmpty() const
{
	return (_private->tools.isEmpty());
}

UTool* UToolList::leftmost()
{
	if (_private->leftmost == NULL)
		_private->leftmost = NewObject<UTool>(this, UTool::StaticClass());
	_private->leftmost->setTool(_private->tools.leftmost());
	return (_private->leftmost);
}

UTool* UToolList::rightmost()
{
	if (_private->rightmost == NULL)
		_private->rightmost = NewObject<UTool>(this, UTool::StaticClass());
	_private->rightmost = NewObject<UTool>(this, UTool::StaticClass());
	_private->rightmost->setTool(_private->tools.rightmost());
	return (_private->rightmost);
}


UTool* UToolList::frontmost()
{

	if (_private->frontmost == NULL)
		_private->frontmost = NewObject<UTool>(this, UTool::StaticClass());
	_private->frontmost = NewObject<UTool>(this, UTool::StaticClass());
	_private->frontmost->setTool(_private->tools.frontmost());
	return (_private->frontmost);
}

UPointable* UToolList::getPointableById(int32 id)
{
	if (_private->pointableById == NULL)
		_private->pointableById = NewObject<UTool>(this, UTool::StaticClass());
	_private->pointableById = NewObject<UTool>(this, UTool::StaticClass());
	_private->pointableById->setPointable(_private->tools[id]);
	return (_private->pointableById);
}

void UToolList::setToolList(const Leap::ToolList &pointables)
{
	_private->tools = pointables;
}
#include "LeapMotionPrivatePCH.h"
#include "ToolList.h"
#include "Tool.h"

UToolList::UToolList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UToolList::~UToolList()
{
}

UToolList *UToolList::append(const UToolList *list)
{
	UToolList *newlist;

	newlist = NewObject<UToolList>(this, UToolList::StaticClass());
	newlist->setToolList(this->_tools.append(list->_tools));
	return (newlist);
}

int32 UToolList::Count() const
{
	return (_tools.count());
}

bool UToolList::isEmpty() const
{
	return (_tools.isEmpty());
}

UTool* UToolList::leftmost()
{
	if (!_leftmost)
		_leftmost = NewObject<UTool>(this, UTool::StaticClass());
	_leftmost->setTool(_tools.leftmost());
	return (_leftmost);
}

UTool* UToolList::rightmost()
{
	if (!_rightmost)
		_rightmost = NewObject<UTool>(this, UTool::StaticClass());
	_rightmost = NewObject<UTool>(this, UTool::StaticClass());
	_rightmost->setTool(_tools.rightmost());
	return (_rightmost);
}


UTool* UToolList::frontmost()
{

	if (!_frontmost)
		_frontmost = NewObject<UTool>(this, UTool::StaticClass());
	_frontmost = NewObject<UTool>(this, UTool::StaticClass());
	_frontmost->setTool(_tools.frontmost());
	return (_frontmost);
}

UPointable* UToolList::getPointableById(int32 id)
{
	if (!_pointableById)
		_pointableById = NewObject<UTool>(this, UTool::StaticClass());
	_pointableById = NewObject<UTool>(this, UTool::StaticClass());
	_pointableById->setPointable(_tools[id]);
	return (_pointableById);
}

void UToolList::setToolList(const Leap::ToolList &pointables)
{
	_tools = pointables;
}
#include "LeapMotionPrivatePCH.h"

UToolList::UToolList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UToolList::~UToolList()
{
}

UToolList *UToolList::append(const UToolList *list)
{
	UToolList *newlist;

	newlist = ConstructObject<UToolList>(UToolList::StaticClass());
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

UTool *UToolList::leftmost()
{
	UTool *pointable;

	pointable = ConstructObject<UTool>(UTool::StaticClass());
	pointable->setTool(_tools.leftmost());
	return (pointable);
}

UTool *UToolList::rightmost()
{
	UTool *pointable;

	pointable = ConstructObject<UTool>(UTool::StaticClass());
	pointable->setTool(_tools.rightmost());
	return (pointable);
}


UTool *UToolList::frontmost()
{
	UTool *pointable;

	pointable = ConstructObject<UTool>(UTool::StaticClass());
	pointable->setTool(_tools.frontmost());
	return (pointable);
}

UTool *UToolList::getPointableById(int32 id)
{
	UTool *pointable;

	pointable = ConstructObject<UTool>(UTool::StaticClass());
	pointable->setTool(_tools[id]);
	return (pointable);
}

void UToolList::setToolList(const Leap::ToolList &pointables)
{
	_tools = pointables;
}
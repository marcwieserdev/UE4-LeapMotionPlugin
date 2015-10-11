#include "LeapMotionPrivatePCH.h"
#include "LeapTool.h"

class PrivateTool
{
public:
	Leap::Tool tool;
};

ULeapTool::ULeapTool(const FObjectInitializer &init) : ULeapPointable(init), _private(new PrivateTool())
{
}

ULeapTool::~ULeapTool()
{
	delete _private;
}

void ULeapTool::setTool(const Leap::Tool &tool)
{
	_private->tool = tool;

	setPointable(_private->tool);
}
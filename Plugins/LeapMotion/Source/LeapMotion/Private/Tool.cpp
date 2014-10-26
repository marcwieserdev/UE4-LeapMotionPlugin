#include "LeapMotionPrivatePCH.h"
#include "Tool.h"

class PrivateTool
{
public:
	Leap::Tool tool;
};

UTool::UTool(const FPostConstructInitializeProperties &init) : UPointable(init), _private(new PrivateTool())
{
}

UTool::~UTool()
{
	delete _private;
}

void UTool::setTool(const Leap::Tool &tool)
{
	_private->tool = tool;

	setPointable(_private->tool);
}
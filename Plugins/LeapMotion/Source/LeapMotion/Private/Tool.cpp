#include "LeapMotionPrivatePCH.h"
#include "Tool.h"

UTool::UTool(const FPostConstructInitializeProperties &init) : UPointable(init)
{
}

UTool::~UTool()
{
}

void UTool::setTool(const Leap::Tool &tool)
{
	_tool = tool;

	setPointable(_tool);
}
#include "LeapMotionPrivatePCH.h"
#include "LeapTool.h"

class PrivateTool
{
public:
	Leap::Tool Tool;
};

ULeapTool::ULeapTool(const FObjectInitializer &ObjectInitializer) : ULeapPointable(ObjectInitializer), Private(new PrivateTool())
{
}

ULeapTool::~ULeapTool()
{
	delete Private;
}

void ULeapTool::SetTool(const Leap::Tool &Tool)
{
	Private->Tool = Tool;

	SetPointable(Private->Tool);
}
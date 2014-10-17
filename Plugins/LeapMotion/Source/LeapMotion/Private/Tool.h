#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Pointable.h"
#include "Tool.generated.h"

UCLASS(BlueprintType)
class UTool : public UPointable
{
	GENERATED_UCLASS_BODY()
public:
	~UTool();

	void setTool(const Leap::Tool &tool);
private:
	Leap::Tool _tool;
};
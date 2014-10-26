#pragma once

#include "LeapMotionPublicPCH.h"
#include "Pointable.h"
#include "Tool.generated.h"

UCLASS(BlueprintType)
class UTool : public UPointable
{
	GENERATED_UCLASS_BODY()
public:
	~UTool();

	void setTool(const class Leap::Tool &tool);

private:
	class PrivateTool* _private;
};
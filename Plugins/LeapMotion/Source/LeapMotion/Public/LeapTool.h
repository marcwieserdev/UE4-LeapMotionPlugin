#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointable.h"
#include "LeapTool.generated.h"

UCLASS(BlueprintType)
class ULeapTool : public ULeapPointable
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapTool();

	void setTool(const class Leap::Tool &tool);

private:
	class PrivateTool* _private;
};
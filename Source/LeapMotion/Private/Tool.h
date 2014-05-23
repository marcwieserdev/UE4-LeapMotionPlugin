#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Tool.generated.h"

UCLASS(BlueprintType)
class UTool : public UPointable
{
	GENERATED_UCLASS_BODY()
public:
	~UTool();

	FVector Direction() const;
	class ULeapFrame *frame();
	class UHand *Hand();
	int32 Id() const;
	bool isExtended() const;
	bool isFinger() const;
	bool isTool() const;
	bool IsValid() const;
	float Length() const;
	bool equal(const UPointable *other) const;
	bool different(const UPointable *other) const;
	FVector stabilizedTipPosition();
	float timeVisible() const;
	FVector tipPosition() const;
	FVector tipVelocity() const;
	float touchDistance() const;
	LeapZone touchZone() const;
	float Width() const;
	void setTool(const Leap::Tool &tool);
private:
	Leap::Tool _tool;
};
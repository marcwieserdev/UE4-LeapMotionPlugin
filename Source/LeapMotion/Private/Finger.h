#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Finger.generated.h"

UCLASS(BlueprintType)
class UFinger : public UPointable
{
	GENERATED_UCLASS_BODY()
public:
	~UFinger();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "bone", CompactNodeTitle = "", Keywords = "get bone"), Category = Leap)
	class UBone *Bone(enum BoneType type);

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
	void setFinger(const Leap::Finger &pointable);
private:
	Leap::Finger _finger;
};
#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Pointable.generated.h"

UENUM(BlueprintType)
enum LeapZone
{
	ZONE_ERROR,
	ZONE_NONE,
	ZONE_HOVERING,
	ZONE_TOUCHING
};

UCLASS(BlueprintType)
class UPointable : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UPointable();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "direction", CompactNodeTitle="", Keywords = "direction"), Category = Leap)
	FVector Direction() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle="", Keywords = "frame"), Category = Leap)
	class ULeapFrame *frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hand", CompactNodeTitle="", Keywords = "hand"), Category = Leap)
	class UHand *Hand();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "id", CompactNodeTitle="", Keywords = "get id"), Category = Leap)
	int32 Id() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isExtended", CompactNodeTitle="", Keywords = "is extended"), Category = Leap)
	bool isExtended() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isFinger", CompactNodeTitle="", Keywords = "is finger"), Category = Leap)
	bool isFinger() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isTool", CompactNodeTitle="", Keywords = "is tool"), Category = Leap)
	bool isTool() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle="", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "length", CompactNodeTitle="", Keywords = "get length"), Category = Leap)
	float Length() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "equal", CompactNodeTitle="==", Keywords = "equal"), Category = Leap)
	bool equal(const UPointable *other) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "different", CompactNodeTitle="!=", Keywords = "different"), Category = Leap)
	bool different(const UPointable *other) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "stabilizedTipPosition", CompactNodeTitle="", Keywords = "stabilized tip position"), Category = Leap)
	FVector stabilizedTipPosition();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "timeVisible", CompactNodeTitle="", Keywords = "get time visible"), Category = Leap)
	float timeVisible() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "tipPosition", CompactNodeTitle="", Keywords = "tip position"), Category = Leap)
	FVector tipPosition() const;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "tipVelocity", CompactNodeTitle="", Keywords = "tip velocity"), Category = Leap)
	FVector tipVelocity() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "touchDistance", CompactNodeTitle="", Keywords = "touch distance"), Category = Leap)
	float touchDistance() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "touchZone", CompactNodeTitle="", Keywords = "touch zone"), Category = Leap)
	LeapZone touchZone() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "width", CompactNodeTitle="", Keywords = "get width"), Category = Leap)
	float Width() const;

	void setPointable(const Leap::Pointable &pointable);
private:
	Leap::Pointable _pointable;
};
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	FVector Direction;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle="", Keywords = "frame"), Category = "Leap Pointable")
	virtual class ULeapFrame *Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hand", CompactNodeTitle="", Keywords = "hand"), Category = "Leap Pointable")
	virtual class UHand *Hand();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	int32 Id;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isExtended", CompactNodeTitle="", Keywords = "is extended"), Category = "Leap Pointable")
	bool IsExtended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isFinger", CompactNodeTitle="", Keywords = "is finger"), Category = "Leap Pointable")
	bool IsFinger();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isTool", CompactNodeTitle="", Keywords = "is tool"), Category = "Leap Pointable")
	bool IsTool();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle="", Keywords = "is valid"), Category = "Leap Pointable")
	bool IsValid();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	float Length;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "equal", CompactNodeTitle="==", Keywords = "equal"), Category = "Leap Pointable")
	virtual bool equal(const UPointable *other);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "different", CompactNodeTitle="!=", Keywords = "different"), Category = "Leap Pointable")
	virtual bool different(const UPointable *other);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	FVector StabilizedTipPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	float TimeVisible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	FVector TipPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	FVector TipVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	float TouchDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	TEnumAsByte<LeapZone> TouchZone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	float Width;

	void setPointable(const Leap::Pointable &pointable);
	const Leap::Pointable &getPointable() const;
private:
	Leap::Pointable _pointable;
};
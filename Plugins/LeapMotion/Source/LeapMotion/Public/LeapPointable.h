#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointable.generated.h"

UCLASS(BlueprintType)
class ULeapPointable : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapPointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	FVector Direction;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle="", Keywords = "frame"), Category = "Leap Pointable")
	virtual class ULeapFrame *Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hand", CompactNodeTitle="", Keywords = "hand"), Category = "Leap Pointable")
	virtual class ULeapHand *Hand();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	bool IsExtended;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	bool IsFinger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	bool IsTool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable")
	float Length;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "equal", CompactNodeTitle="==", Keywords = "equal"), Category = "Leap Pointable")
	virtual bool equal(const ULeapPointable *other);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "different", CompactNodeTitle="!=", Keywords = "different"), Category = "Leap Pointable")
	virtual bool different(const ULeapPointable *other);

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

	void setPointable(const class Leap::Pointable &pointable);
	const Leap::Pointable &getPointable() const;

	virtual void CleanupRootReferences();

private:
	class PrivatePointable* _private;
};
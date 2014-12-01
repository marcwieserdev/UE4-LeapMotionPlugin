#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapSwipeGesture.generated.h"

UCLASS(BlueprintType)
class ULeapSwipeGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapSwipeGesture();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	TEnumAsByte<LeapBasicDirection> BasicDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Direction;

	UFUNCTION(BlueprintCallable, Category = "Leap Swipe Gesture")
	class ULeapPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector StartPosition;
	
	void setGesture(const class Leap::SwipeGesture &Gesture);

	virtual void CleanupRootReferences();

private:
	class PrivateSwipeGesture* _private;
};
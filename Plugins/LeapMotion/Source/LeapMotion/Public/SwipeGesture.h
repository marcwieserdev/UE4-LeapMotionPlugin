#pragma once

#include "LeapMotionPublicPCH.h"
#include "Gesture.h"
#include "SwipeGesture.generated.h"

UCLASS(BlueprintType)
class USwipeGesture : public UGesture
{
	GENERATED_UCLASS_BODY()
public:
	~USwipeGesture();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	TEnumAsByte<LeapPluginDirection> CardinalDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Direction;

	UFUNCTION(BlueprintCallable, Category = "Leap Swipe Gesture")
	class UPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Swipe Gesture")
	FVector StartPosition;
	
	void setGesture(const class Leap::SwipeGesture &Gesture);

private:
	class PrivateSwipeGesture* _private;
};
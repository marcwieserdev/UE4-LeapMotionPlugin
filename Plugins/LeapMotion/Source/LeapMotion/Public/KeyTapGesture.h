#pragma once

#include "LeapMotionPublicPCH.h"
#include "Gesture.h"
#include "KeyTapGesture.generated.h"

UCLASS(BlueprintType)
class UKeyTapGesture : public UGesture
{
	GENERATED_UCLASS_BODY()
public:
	~UKeyTapGesture();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap  Gesture")
	TEnumAsByte<LeapPluginDirection> CardinalDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	FVector Direction;

	UFUNCTION(BlueprintCallable, Category = "Leap Key Tap Gesture")
	class UPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Key Tap Gesture")
	float Progress;

	void setGesture(const class Leap::KeyTapGesture &Gesture);

private:
	class PrivateKeyTapGesture* _private;
};
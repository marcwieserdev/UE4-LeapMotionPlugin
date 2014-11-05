#pragma once

#include "LeapMotionPublicPCH.h"
#include "Gesture.h"
#include "ScreenTapGesture.generated.h"


UCLASS(BlueprintType)
class UScreenTapGesture : public UGesture
{
	GENERATED_UCLASS_BODY()
public:
	~UScreenTapGesture();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap  Gesture")
	TEnumAsByte<LeapPluginDirection> CardinalDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	FVector Direction;

	UFUNCTION(BlueprintCallable, Category = "Leap Screen Tap Gesture")
	class UPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	float Progress;

	void setGesture(const class Leap::ScreenTapGesture &Gesture);

private:
	class PrivateScreenTapGesture* _private;
};
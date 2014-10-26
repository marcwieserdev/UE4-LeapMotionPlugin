#pragma once

#include "LeapMotionPublicPCH.h"
#include "Gesture.h"
#include "CircleGesture.generated.h"


UCLASS(BlueprintType)
class UCircleGesture : public UGesture
{
	GENERATED_UCLASS_BODY()
public:
	~UCircleGesture();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Normal;

	UFUNCTION(BlueprintCallable, Category = "Leap Circle Gesture")
	class UPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Progress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Radius;

	void setGesture(const class Leap::CircleGesture &Gesture);

private:
	class PrivateCircleGesture* _private;
};
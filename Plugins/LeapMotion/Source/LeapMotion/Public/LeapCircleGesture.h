#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapCircleGesture.generated.h"


UCLASS(BlueprintType)
class ULeapCircleGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapCircleGesture();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	FVector Normal;

	UFUNCTION(BlueprintCallable, Category = "Leap Circle Gesture")
	class ULeapPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Progress;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Circle Gesture")
	float Radius;

	void setGesture(const class Leap::CircleGesture &Gesture);

	virtual void CleanupRootReferences();

private:
	class PrivateCircleGesture* _private;
};
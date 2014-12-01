#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapScreenTapGesture.generated.h"


UCLASS(BlueprintType)
class ULeapScreenTapGesture : public ULeapGesture
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapScreenTapGesture();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap  Gesture")
	TEnumAsByte<LeapBasicDirection> BasicDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	FVector Direction;

	UFUNCTION(BlueprintCallable, Category = "Leap Screen Tap Gesture")
	class ULeapPointable* Pointable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Screen Tap Gesture")
	float Progress;

	void setGesture(const class Leap::ScreenTapGesture &Gesture);

	virtual void CleanupRootReferences();

private:
	class PrivateScreenTapGesture* _private;
};
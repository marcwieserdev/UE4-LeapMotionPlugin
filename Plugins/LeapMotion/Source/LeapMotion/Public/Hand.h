#pragma once

#include "LeapMotionPublicPCH.h"
#include "Hand.generated.h"

UCLASS(BlueprintType)
class UHand : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UHand();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	class UArm* Arm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	bool IsLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	bool IsRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector PalmNormal;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector PalmPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector PalmVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FMatrix Basis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float Confidence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector Direction;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Frame"), Category = "Leap Hand")
	class ULeapFrame* Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Fingers"), Category = "Leap Hand")
	class UFingerList* Fingers();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float GrabStrength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float PalmWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float PinchStrength;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RotationAngle"), Category = "Leap Hand")
	float RotationAngle(class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RotationAngleWithAxis"), Category = "Leap Hand")
	float RotationAngleWithAxis(class ULeapFrame *otherFrame, const FVector &axis);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RotationMatrix"), Category = "Leap Hand")
	FMatrix RotationMatrix(const class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RotationAxis"), Category = "Leap Hand")
	FVector RotationAxis(const class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "RotationProbability"), Category = "Leap Hand")
	float RotationProbability(const class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "ScaleFactor"), Category = "Leap Hand")
	float ScaleFactor(const class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "ScaleProbability"), Category = "Leap Hand")
	float ScaleProbability(const class ULeapFrame *otherFrame);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector SphereCenter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	FVector StabilizedPalmPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	float TimeVisible;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Translation"), Category = "Leap Hand")
	FVector Translation(const class ULeapFrame *otherFrame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "TranslationProbability"), Category = "Leap Hand")
	float TranslationProbability(const class ULeapFrame *otherFrame);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand")
	int32 Id;

	bool operator!=(const UHand &) const;

	bool operator==(const UHand &) const;

	void setHand(const class Leap::Hand &hand);

private:
	class PrivateHand* _private;
};
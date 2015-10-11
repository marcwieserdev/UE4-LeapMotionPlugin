#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapArm.generated.h"

UCLASS(BlueprintType)
class ULeapArm : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapArm();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FMatrix Basis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector ElbowPosition;

	UFUNCTION(BlueprintCallable, Category = "Leap Arm")
	FRotator GetOrientation(LeapHandType handType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector WristPosition;

	bool operator!=(const ULeapArm &) const;

	bool operator==(const ULeapArm &) const; 

	void setArm(const class Leap::Arm &arm);

	virtual void CleanupRootReferences();

private:
	class PrivateArm* _private;
};
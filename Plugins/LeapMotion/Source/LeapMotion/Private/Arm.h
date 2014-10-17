#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Arm.generated.h"

UCLASS(BlueprintType)
class UArm : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UArm();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FMatrix Basis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector ElbowPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	float Width;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Arm")
	FVector WristPosition;

	bool operator!=(const UArm &) const;

	bool operator==(const UArm &) const;

	void setArm(const Leap::Arm &arm);
private:
	Leap::Arm _arm;
};
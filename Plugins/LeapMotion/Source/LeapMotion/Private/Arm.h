#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Arm.generated.h"

UCLASS(BlueprintType)
class UArm : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UArm();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "basis", CompactNodeTitle = "", Keywords = "get basis"), Category = Leap)
	FMatrix basis();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "center", CompactNodeTitle = "", Keywords = "get center"), Category = Leap)
	FVector Center();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "direction", CompactNodeTitle = "", Keywords = "get direction"), Category = Leap)
	FVector Direction();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "elbowPosition", CompactNodeTitle = "", Keywords = "get elbow position"), Category = Leap)
	FVector elbowPosition();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "width", CompactNodeTitle = "", Keywords = "get width"), Category = Leap)
	float Width();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "wristPosition", CompactNodeTitle = "", Keywords = "get wrist position"), Category = Leap)
	FVector wristPosition();

	bool operator!=(const UArm &) const;

	bool operator==(const UArm &) const;

	void setArm(const Leap::Arm &arm);
private:
	Leap::Arm _arm;
};
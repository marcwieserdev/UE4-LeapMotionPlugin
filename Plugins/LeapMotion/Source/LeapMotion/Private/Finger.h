#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Pointable.h"
#include "Finger.generated.h"

UCLASS(BlueprintType)
class UFinger : public UPointable
{
	GENERATED_UCLASS_BODY()
public:
	~UFinger();

	UFUNCTION(BlueprintCallable, meta = (Category = "Leap Finger"))
	class UBone *Bone(enum BoneType type);

	//Convenience Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class UBone *Metacarpal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class UBone *Proximal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class UBone *Intermediate;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger")
	class UBone *Distal;


	void setFinger(const Leap::Finger &pointable);

private:
	Leap::Finger _finger;
};
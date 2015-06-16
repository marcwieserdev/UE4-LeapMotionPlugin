#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapBone.generated.h"

UCLASS(BlueprintType)
class ULeapBone : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapBone();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FMatrix Basis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Direction;

	//Convenience method, requires knowledge of the hand this bone belongs to in order to give a correct orientation (left hand basis is different from right).
	UFUNCTION(BlueprintCallable, Category = "Leap Bone")
	FRotator GetOrientation(LeapHandType handType);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector NextJoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector PrevJoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	TEnumAsByte<LeapBoneType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Width;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "different", CompactNodeTitle = "!=", Keywords = "different operator"), Category = "Leap Bone")
	bool different(const ULeapBone *other) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "equal", CompactNodeTitle = "==", Keywords = "equal operator"), Category = "Leap Bone")
	bool equal(const ULeapBone *other) const;

	void setBone(const class Leap::Bone &bone);

	virtual void CleanupRootReferences();

private:
	class PrivateBone* _private;
};
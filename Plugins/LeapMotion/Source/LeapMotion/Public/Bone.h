#pragma once

#include "LeapMotionPublicPCH.h"
#include "Bone.generated.h"

UENUM(BlueprintType)
enum BoneType
{
	TYPE_METACARPAL,
	TYPE_PROXIMAL,
	TYPE_INTERMEDIATE,
	TYPE_DISTAL,
	TYPE_ERROR
};

UCLASS(BlueprintType)
class UBone : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UBone();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FMatrix Basis;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Center;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Length;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector NextJoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	FVector PrevJoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	TEnumAsByte<BoneType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Bone")
	float Width;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "different", CompactNodeTitle = "!=", Keywords = "different operator"), Category = Leap)
	bool different(const UBone *other) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "equal", CompactNodeTitle = "==", Keywords = "equal operator"), Category = Leap)
	bool equal(const UBone *other) const;

	void setBone(const class Leap::Bone &bone);

private:
	class PrivateBone* _private;
};
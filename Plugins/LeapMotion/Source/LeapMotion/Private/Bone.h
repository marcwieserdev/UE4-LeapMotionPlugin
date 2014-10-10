#pragma once

#include "LeapMotionPrivatePCH.h"
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

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "basis", CompactNodeTitle = "", Keywords = "get basis"), Category = Leap)
	FMatrix basis() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "center", CompactNodeTitle = "", Keywords = "get center"), Category = Leap)
	FVector Center() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "direction", CompactNodeTitle = "", Keywords = "get direction"), Category = Leap)
	FVector Direction() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "length", CompactNodeTitle = "", Keywords = "get length"), Category = Leap)
	float Length() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "nextJoint", CompactNodeTitle = "", Keywords = "get next joint"), Category = Leap)
	FVector nextJoint() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "equal", CompactNodeTitle = "==", Keywords = "equal operator"), Category = Leap)
	bool equal(const UBone *other) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "different", CompactNodeTitle = "!=", Keywords = "different operator"), Category = Leap)
	bool different(const UBone *other) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "prevJoint", CompactNodeTitle = "", Keywords = "get prev joint"), Category = Leap)
	FVector prevJoint() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "type", CompactNodeTitle = "", Keywords = "get type"), Category = Leap)
	BoneType Type() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "width", CompactNodeTitle = "", Keywords = "get width"), Category = Leap)
	float Width() const;

	void setBone(const Leap::Bone &bone);
private:
	Leap::Bone _bone;
};
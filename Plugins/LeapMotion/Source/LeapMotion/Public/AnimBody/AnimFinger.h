#pragma once

#include "AnimBone.h"
#include "LeapEnums.h"
#include "AnimFinger.generated.h"

/**
* Animation Finger object used to hold tracked animation state and provide
* convenience functions for re-basing and shifting tracked finger data.
*/
UENUM(BlueprintType)
enum AnimHandType
{
	ANIM_HAND_UNKNOWN,
	ANIM_HAND_LEFT,
	ANIM_HAND_RIGHT
};

UCLASS(BlueprintType)
class LEAPMOTION_API UAnimFinger : public UObject
{
	GENERATED_UCLASS_BODY()

	/**
	* Metacarpal Animation Bone
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Metacarpal;

	/**
	* Proximal Animation Bone
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Proximal;

	/**
	* Intermediate Animation Bone
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Intermediate;

	/**
	* Distal Animation Bone
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Finger")
	UAnimBone* Distal;

	/**
	* Animation alpha blend
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Finger")
	float Alpha;

	/**
	* Check whether alpha blend is 1.f
	*
	* @return  True if alpha is 1.f
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	bool Enabled();

	/**
	* Set enabled state for animation query, Alpha = 1.f
	* Will affect a child bones.
	*
	* @param  Enable default to true
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetEnabled(bool Enable = true);

	/**
	* Translate all the bones in the finger by given vector amount
	*
	* @param  Shift		Vector amount
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void TranslateFinger(FVector Shift);

	/**
	* Changes the Basis by rotations sets. Used for rotating from XForward to YForward defaults
	* in animation.
	*
	* @param  PreBase		Basis offset affecting input
	* @param  PostBase		Fixed offset not affecting input
	* @param  AdjustVectors Whether the basis should affect vectors or just orientation
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);

	/**
	* Convenience function to copy the state of the AnimFinger from the LeapFinger
	*
	* @param Finger finger to copy from
	* @param HandType left or right
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Finger")
	void SetFromLeapFinger(class ULeapFinger* Finger, LeapHandType HandType);
};
#pragma once

#include "Core.h"
#include "AnimBone.generated.h"

/**
* Animation Finger object used to hold tracked animation state and provide
* convenience functions for re-basing and shifting tracked finger data.
*/
UCLASS(BlueprintType)
class LEAPMOTION_API UAnimBone : public UObject
{
	GENERATED_UCLASS_BODY()

	/**
	* Bone raw transform position.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Position;

	/**
	* Bone raw transform orientation.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FRotator Orientation;

	/**
	* Bone raw transform scale.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Scale;

	/**
	* Bone Length in cm.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Length;

	/**
	* Tracked state alpha. Vary the value to blend animation with tracked information.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Alpha;


	/**
	* Optional vector of the previous joint (outward)
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector NextJoint;


	/**
	* Optional vector of the previous joint (inward)
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector PrevJoint;

	/**
	* Check whether alpha blend is 1.f
	*
	* @return  True if alpha is 1.f
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	bool Enabled();

	/**
	* Set enabled state for animation query, Alpha = 1.f
	*
	* @param  Enable default to true
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetEnabled(bool Enable = true);

	/**
	* Sets raw values from transform
	*
	* @param  Transform		Transform
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetFromTransform(const FTransform& Transform);

	/**
	* Transform from raw values
	* @return Transform
	*/
	UFUNCTION(BlueprintPure, Category = "Anim Bone")
	FTransform GetTransform();

	/**
	* Moves the bone by given amount
	*
	* @param  Shift		Vector amount
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void TranslateBone(FVector Shift);


	/**
	* Transform the bone by the given transform
	*
	* @param ByTransform	Affecting transform
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void TransformBone(FTransform& ByTransform);
	
	/**
	* Changes the Basis by rotations sets. Used for rotating from XForward to YForward defaults
	* in animation.
	*
	* @param  PreBase		Basis offset affecting input
	* @param  PostBase		Fixed offset not affecting input
	* @param  AdjustVectors Whether the basis should affect vectors or just orientation
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);
};
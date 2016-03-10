#pragma once

#include "AnimHand.h"
#include "AnimBody.generated.h"

/**
* Animation Body object used to hold tracked animation state and provide
* convenience functions for re-basing and shifting the whole skeleton data.
*/
UCLASS(ClassGroup = "Animation Skeleton", meta = (BlueprintSpawnableComponent))
class LEAPMOTION_API UAnimBody : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	/**
	* Tracked state alpha. Vary the value to blend animation with tracked information.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Anim Body")
	float Alpha;

	/**
	* Left Anim Hand
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimHand* Left;

	/**
	* Right Anim Hand
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimHand* Right;

	/**
	* Head Bone
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Body")
	UAnimBone* Head;

	/**
	* Check whether alpha blend is 1.f
	*
	* @return  True if alpha is 1.f
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	bool Enabled();

	/**
	* Set enabled state for animation query, Alpha = 1.f.
	* Will affect a child bones.
	*
	* @param  Enable default to true
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void SetEnabled(bool Enable = true);

	/**
	* Translate all the bones in the body by given vector amount
	*
	* @param  Shift		Vector amount
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void TranslateBody(FVector Shift);

	/**
	* Changes the Basis by rotations sets. Used for rotating from XForward to YForward defaults
	* in animation.
	*
	* @param  PreBase		Basis offset affecting input
	* @param  PostBase		Fixed offset not affecting input
	* @param  AdjustVectors Whether the basis should affect vectors or just orientation
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Body")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);
};
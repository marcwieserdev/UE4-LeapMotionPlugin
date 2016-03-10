#pragma once

#include "AnimFinger.h"
#include "LeapHand.h"
#include "AnimHand.generated.h"

/**
* Animation Hand object used to hold tracked animation state and provide
* convenience functions for re-basing and shifting tracked hand data.
*/
UCLASS(BlueprintType)
class LEAPMOTION_API UAnimHand : public UObject
{
	GENERATED_UCLASS_BODY()

	/**
	* Tracked state alpha. Vary the value to blend animation with tracked information.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim Hand")
	float Alpha;

	/**
	* Confidence in pose as determined by tracking
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Hand")
	float Confidence;

	//Fingers

	/**
	* Tracked thumb finger.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Thumb;

	/**
	* Tracked index finger.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Index;
	
	/**
	* Tracked middle finger.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Middle;

	/**
	* Tracked ring finger.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Ring;

	/**
	* Tracked pinky finger.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand Finger")
	UAnimFinger* Pinky;
	
	/**
	* Tracked wrist bone.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* Wrist;

	/**
	* Tracked palm bone.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* Palm;
	
	/**
	* Tracked lowerarm bone.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Anim Hand")
	UAnimBone* LowerArm;

	/**
	* Check whether alpha blend is 1.f
	*
	* @return  True if alpha is 1.f
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	bool Enabled();

	/**
	* Set enabled state for animation query, Alpha = 1.f
	* Will affect a child bones.
	*
	* @param  Enable default to true
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void SetEnabled(bool Enable = true);

	/**
	* Translate all the bones in the hand by given vector amount
	*
	* @param  Shift		Vector amount
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void TranslateHand(FVector Shift);

	/**
	* Changes the Basis by rotations sets. Used for rotating from XForward to YForward defaults
	* in animation.
	*
	* @param  PreBase		Basis offset affecting input
	* @param  PostBase		Fixed offset not affecting input
	* @param  AdjustVectors Whether the basis should affect vectors or just orientation
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors = true);


	/**
	* Convenience function to copy the state of the AnimHand from the LeapHand
	*
	* @param Hand hand to copy from
	*/
	UFUNCTION(BlueprintCallable, Category = "Anim Hand")
	void SetFromLeapHand(class ULeapHand* LeapHand);
};
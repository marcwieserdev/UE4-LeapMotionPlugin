#pragma once

#include "Core.h"
#include "AnimBone.generated.h"

UCLASS(BlueprintType)
class UAnimBone : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Position;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FRotator Orientation;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	FVector Scale;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Length;

	UPROPERTY(BlueprintReadWrite, Category = "Anim Bone")
	float Alpha;


	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	bool Enabled();

	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetEnabled(bool enable = true);

	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void SetFromTransform(FTransform in);

	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	FTransform GetTransform();

	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void TranslateBone(FVector shift);

	UFUNCTION(BlueprintCallable, Category = "Anim Bone")
	void ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors = true);
};
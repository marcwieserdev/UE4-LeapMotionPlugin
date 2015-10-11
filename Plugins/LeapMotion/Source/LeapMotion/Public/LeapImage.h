#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapImage.generated.h"


UCLASS(BlueprintType)
class ULeapImage : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImage();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Texture", CompactNodeTitle = "", Keywords = "get texture"), Category = "Leap Image")
	class UTexture2D* Texture();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "R8Texture", CompactNodeTitle = "", Keywords = "get texture single channel"), Category = "Leap Image")
	class UTexture2D* R8Texture();
	
	//Faster raw distortion (R=U, G=V), requires channel conversion, 32bit float per channel texture will look odd if rendered raw.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distortion", CompactNodeTitle = "", Keywords = "distortion"), Category = "Leap Image")
	class UTexture2D* Distortion();

	//Visually correct distortion in UE format (R=U, G=1-V) at the cost of additional CPU time (roughly 1ms) in 8bit per channel format
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Distortion UE", CompactNodeTitle = "", Keywords = "distortion ue"), Category = "Leap Image")
	class UTexture2D* DistortionUE();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 DistortionHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 DistortionWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	bool IsValid;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayOffsetX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayOffsetY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayScaleX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	float RayScaleY;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "rectify", CompactNodeTitle = "", Keywords = "rectify"), Category = "Leap Image")
	FVector Rectify(FVector uv) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "warp", CompactNodeTitle = "", Keywords = "warp"), Category = "Leap Image")
	FVector Warp(FVector xy) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Width;

	void setLeapImage(const class Leap::Image &LeapImage);

	virtual void CleanupRootReferences();

private:
	class PrivateLeapImage* _private;
};
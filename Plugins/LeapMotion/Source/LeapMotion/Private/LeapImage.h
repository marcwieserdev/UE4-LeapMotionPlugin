#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapImage.generated.h"


UCLASS(BlueprintType)
class ULeapImage : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImage();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Texture", CompactNodeTitle = "", Keywords = "get texture"), Category = "Leap Image")
	class UTexture2D* Texture();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "R8Texture", CompactNodeTitle = "", Keywords = "get texture single channel"), Category = "Leap Image")
	class UTexture2D* R8Texture();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Distortion", CompactNodeTitle = "", Keywords = "distortion"), Category = "Leap Image")
	class UTexture2D* Distortion();

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

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rectify", CompactNodeTitle = "", Keywords = "rectify"), Category = "Leap Image")
	FVector Rectify(FVector uv) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "warp", CompactNodeTitle = "", Keywords = "warp"), Category = "Leap Image")
	FVector Warp(FVector xy) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image")
	int32 Width;

	void setLeapImage(const Leap::Image &LeapImage);

private:
	UTexture2D* imagePointer;
	UTexture2D* distortionPointer;

	bool validImagePointer();
	UTexture2D* Texture8FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapImage(int32 SrcWidth, int32 SrcHeight, uint8* imageBuffer);
	UTexture2D* Texture32FromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);
	UTexture2D* TextureFFromLeapDistortion(int32 SrcWidth, int32 SrcHeight, float* imageBuffer);
	Leap::Image _leapImage;
};
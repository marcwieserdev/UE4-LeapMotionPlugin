#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapImage.generated.h"


UCLASS(BlueprintType)
class ULeapImage : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImage();

	//Not ready
	//UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Texture", CompactNodeTitle = "", Keywords = "get texture"), Category = Leap)
	//class UTexture2D* GetTexture();	//UTexture2D*
	
	//Not really appropriate for bp
	//UFUNCTION(BlueprintCallable, meta = (FriendlyName = "distortion", CompactNodeTitle = "", Keywords = "distortion"), Category = Leap)
	const float* Distortion() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "distortionHeight", CompactNodeTitle = "", Keywords = "distortion height"), Category = Leap)
	int32 DistortionHeight() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "distortionWidth", CompactNodeTitle = "", Keywords = "distortion width"), Category = Leap)
	int32 DistortionWidth() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "height", CompactNodeTitle = "", Keywords = "get height"), Category = Leap)
	int32 Height();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "id", CompactNodeTitle = "", Keywords = "id"), Category = Leap)
	int32 Id() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rayOffsetX", CompactNodeTitle = "", Keywords = "ray offset x"), Category = Leap)
	float RayOffsetX() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rayOffsetY", CompactNodeTitle = "", Keywords = "ray offset y"), Category = Leap)
	float RayOffsetY() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rayScaleX", CompactNodeTitle = "", Keywords = "ray scale x"), Category = Leap)
	float RayScaleX() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rayScaleY", CompactNodeTitle = "", Keywords = "ray scale y"), Category = Leap)
	float RayScaleY() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rectify", CompactNodeTitle = "", Keywords = "rectify"), Category = Leap)
	FVector Rectify(FVector uv) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "warp", CompactNodeTitle = "", Keywords = "warp"), Category = Leap)
	FVector Warp(FVector xy) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "width", CompactNodeTitle = "", Keywords = "get width"), Category = Leap)
	int32 Width();

	void setLeapImage(const Leap::Image &LeapImage);

private:
	UTexture2D* LeapDataToTexture(const int32 SrcWidth, const int32 SrcHeight, const TArray<int8> &SrcData, const bool UseAlpha);
	Leap::Image _leapImage;
};
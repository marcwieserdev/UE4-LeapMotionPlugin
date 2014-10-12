#pragma once

#include "LeapMotionPrivatePCH.h"
#include "InteractionBox.generated.h"

UCLASS(BlueprintType)
class UInteractionBox : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UInteractionBox();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "center", CompactNodeTitle = "", Keywords = "center"), Category = Leap)
	FVector Center() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "denormalizePoint", CompactNodeTitle = "", Keywords = "denormalize point"), Category = Leap)
	FVector DenormalizePoint(FVector position) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "depth", CompactNodeTitle = "", Keywords = "depth"), Category = Leap)
	float Depth() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "height", CompactNodeTitle = "", Keywords = "height"), Category = Leap)
	float Height() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "normalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = Leap)
	FVector NormalizePoint(FVector position, bool clamp=true) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "width", CompactNodeTitle = "", Keywords = "height"), Category = Leap)
	float Width() const;
	
	void setInteractionBox(const Leap::InteractionBox &InteractionBox);

private:
	Leap::InteractionBox _interactionBox;
};
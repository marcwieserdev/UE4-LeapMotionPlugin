#pragma once

#include "LeapMotionPublicPCH.h"
#include "InteractionBox.generated.h"

UCLASS(BlueprintType)
class UInteractionBox : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UInteractionBox();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	FVector Center;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "DenormalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector DenormalizePoint(FVector position) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	bool IsValid;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "normalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector NormalizePoint(FVector position, bool clamp=true) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Width;

	void setInteractionBox(const class Leap::InteractionBox &InteractionBox);

private:
	class PrivateInteractionBox* _private;

};
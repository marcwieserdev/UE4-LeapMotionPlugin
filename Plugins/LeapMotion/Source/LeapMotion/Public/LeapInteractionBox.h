#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapInteractionBox.generated.h"

UCLASS(BlueprintType)
class ULeapInteractionBox : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapInteractionBox();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	FVector Center;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "DenormalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector DenormalizePoint(FVector position) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Depth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	bool IsValid;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "normalizePoint", CompactNodeTitle = "", Keywords = "normalize point"), Category = "Leap Interaction Box")
	FVector NormalizePoint(FVector position, bool clamp=true) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Interaction Box")
	float Width;

	void setInteractionBox(const class Leap::InteractionBox &InteractionBox);

	virtual void CleanupRootReferences();

private:
	class PrivateInteractionBox* _private;

};
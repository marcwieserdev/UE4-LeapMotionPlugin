#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Hand.generated.h"

UCLASS(BlueprintType)
class UHand : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UHand();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isLeft", CompactNodeTitle = "", Keywords = "is left"), Category = Leap)
	bool isLeft() const;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isRight", CompactNodeTitle = "", Keywords = "is right"), Category = Leap)
	bool isRight() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "palmNormal", CompactNodeTitle = "", Keywords = "palm normal"), Category = Leap)
	FVector palmNormal() const;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "palmPosition", CompactNodeTitle = "", Keywords = "palm position"), Category = Leap)
	FVector palmPosition() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "palmVelocity", CompactNodeTitle = "", Keywords = "palm velocity"), Category = Leap)
	FVector palmVelocity() const;

	//TODO : basis()

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "confidence", CompactNodeTitle = "", Keywords = "get confidence"), Category = Leap)
	float confidence() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "direction", CompactNodeTitle = "", Keywords = "get direction"), Category = Leap)
	FVector Direction() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle = "", Keywords = "get frame"), Category = Leap)
	class ULeapFrame *frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "strength", CompactNodeTitle = "", Keywords = "get strength"), Category = Leap)
	float grabStrength() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "id", CompactNodeTitle = "", Keywords = "get id"), Category = Leap)
	int32 Id() const;

	void setHand(const Leap::Hand &hand);
private:
	Leap::Hand _hand;
};
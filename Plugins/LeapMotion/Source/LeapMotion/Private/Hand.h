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

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "basis", CompactNodeTitle = "", Keywords = "get basis"), Category = Leap)
	FMatrix basis();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "confidence", CompactNodeTitle = "", Keywords = "get confidence"), Category = Leap)
	float confidence() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "direction", CompactNodeTitle = "", Keywords = "get direction"), Category = Leap)
	FVector Direction() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle = "", Keywords = "get frame"), Category = Leap)
	class ULeapFrame *Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "strength", CompactNodeTitle = "", Keywords = "get strength"), Category = Leap)
	float grabStrength() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "palmWidth", CompactNodeTitle = "", Keywords = "get palm Width"), Category = Leap)
	float palmWidth() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "pinchStrength", CompactNodeTitle = "", Keywords = "get pinch strength"), Category = Leap)
	float pinchStrength() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rotationAngle", CompactNodeTitle = "", Keywords = "get rotation angle"), Category = Leap)
	float RotationAngle(class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rotationAngleWithAxis", CompactNodeTitle = "", Keywords = "get rotation angle axis"), Category = Leap)
	float rotationAngleWithAxis(class ULeapFrame *frame, const FVector &axis);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rotationMatrix", CompactNodeTitle = "", Keywords = "get rotation matrix"), Category = Leap)
	FMatrix rotationMatrix(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rotationAxis", CompactNodeTitle = "", Keywords = "get rotation axis"), Category = Leap)
	FVector rotationAxis(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rotationProbability", CompactNodeTitle = "", Keywords = "get rotation probability"), Category = Leap)
	float rotationProbability(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "scaleFactor", CompactNodeTitle = "", Keywords = "get scale factor"), Category = Leap)
	float ScaleFactor(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "scaleProbability", CompactNodeTitle = "", Keywords = "get scale probability"), Category = Leap)
	float scaleProbability(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "sphereCenter", CompactNodeTitle = "", Keywords = "get sphere center"), Category = Leap)
	FVector sphereCenter();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "sphereRadius", CompactNodeTitle = "", Keywords = "get sphere radius"), Category = Leap)
	float SphereRadius() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "stabilizedPalmPosition", CompactNodeTitle = "", Keywords = "get stabilized palm position"), Category = Leap)
	FVector stabilizedPalmPosition();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "timeVisible", CompactNodeTitle = "", Keywords = "get time visible"), Category = Leap)
	float timeVisible() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "translation", CompactNodeTitle = "", Keywords = "get translation"), Category = Leap)
	FVector Translation(const class ULeapFrame *frame);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "translationProbability", CompactNodeTitle = "", Keywords = "get translation probability"), Category = Leap)
	float translationProbability(const class ULeapFrame *frame) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "id", CompactNodeTitle = "", Keywords = "get id"), Category = Leap)
	int32 Id() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Fingers", CompactNodeTitle = "", Keywords = "get fingers"), Category = Leap)
	UFingerList* fingers();

	bool operator!=(const UHand &) const;

	bool operator==(const UHand &) const;

	void setHand(const Leap::Hand &hand);
private:
	Leap::Hand _hand;
};
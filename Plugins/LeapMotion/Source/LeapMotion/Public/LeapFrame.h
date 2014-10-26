#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapFrame.generated.h"

UCLASS(BlueprintType)
class ULeapFrame : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapFrame();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Frame")
	bool IsValid;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getHands", CompactNodeTitle = "", Keywords = "get hands"), Category = "Leap Frame")
	class UHandList* Hands();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "fingers", CompactNodeTitle = "", Keywords = "get fingers"), Category = "Leap Frame")
	class UFingerList* Fingers();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "gestures", CompactNodeTitle = "", Keywords = "get gestures"), Category = "Leap Frame")
	class UGestureList* Gestures();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "interactionBox", CompactNodeTitle = "", Keywords = "get interaction box"), Category = "Leap Frame")
	class UInteractionBox* InteractionBox();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "pointables", CompactNodeTitle = "", Keywords = "get pointables"), Category = "Leap Frame")
	class UPointableList* Pointables();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "images", CompactNodeTitle = "", Keywords = "get images"), Category = "Leap Frame")
	class ULeapImageList* Images();

	//Todo: If appropriate rotationAngle->Matrix, scaleFactor, translation

	void setFrame(Leap::Controller &leap, int history = 0);
	void setFrame(const class Leap::Frame &frame);
	const Leap::Frame &getFrame() const;

private:
	class PrivateLeapFrame* _private;
};
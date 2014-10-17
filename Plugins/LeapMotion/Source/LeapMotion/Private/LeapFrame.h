#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapFrame.generated.h"

UCLASS(BlueprintType)
class ULeapFrame : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapFrame();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getHands", CompactNodeTitle = "", Keywords = "get hands"), Category = Leap)
	class UHandList* Hands();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "fingers", CompactNodeTitle = "", Keywords = "get fingers"), Category = Leap)
	class UFingerList* Fingers();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "gestures", CompactNodeTitle = "", Keywords = "get gestures"), Category = Leap)
	class UGestureList* Gestures();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "interactionBox", CompactNodeTitle = "", Keywords = "get interaction box"), Category = Leap)
	class UInteractionBox* InteractionBox();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "pointables", CompactNodeTitle = "", Keywords = "get pointables"), Category = Leap)
	class UPointableList* Pointables();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "images", CompactNodeTitle = "", Keywords = "get images"), Category = Leap)
	class ULeapImageList* Images();

	//Todo: If appropriate rotationAngle->Matrix, scaleFactor, translation

	void setFrame(Leap::Controller &leap, int history = 0);
	void setFrame(const Leap::Frame &frame);
	const Leap::Frame &getFrame() const;
private:
	Leap::Frame _frame;
};
 
#pragma once

#include "Hand.h"
#include "LeapEventInterface.generated.h"


UINTERFACE(MinimalAPI)
class ULeapEventInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ILeapEventInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	//Hands
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandMoved", CompactNodeTitle = "", Keywords = "hand moved"), Category = "Leap Interface Event")
	void LeapHandMoved(UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeftHandMoved", CompactNodeTitle = "", Keywords = "left hand moved"), Category = "Leap Interface Event")
	void LeapLeftHandMoved(UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "RightHandMoved", CompactNodeTitle = "", Keywords = "right hand moved"), Category = "Leap Interface Event")
	void LeapRightHandMoved(UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandGrabbed", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandGrabbed(float strength, UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandReleased", CompactNodeTitle = "", Keywords = "hand released ungrab"), Category = "Leap Interface Event")
	void LeapHandReleased(float strength, UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandPinched", CompactNodeTitle = "", Keywords = "hand pinch"), Category = "Leap Interface Event")
	void LeapHandPinched(float strength, UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandUnpinched", CompactNodeTitle = "", Keywords = "hand unpinch"), Category = "Leap Interface Event")
	void LeapHandUnpinched(float strength, UHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandCountChanged", CompactNodeTitle = "", Keywords = "hand count"), Category = "Leap Interface Event")
	void HandCountChanged(int32 count);

	//Fingers
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FingerMoved", CompactNodeTitle = "", Keywords = "finger moved"), Category = "Leap Interface Event")
	void LeapFingerMoved(UFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FrontFingerMoved", CompactNodeTitle = "", Keywords = "finger front most moved"), Category = "Leap Interface Event")
	void LeapFrontMostFingerMoved(UFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeftFingerMoved", CompactNodeTitle = "", Keywords = "finger left most moved"), Category = "Leap Interface Event")
	void LeapRightMostFingerMoved(UFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "RightFingerMoved", CompactNodeTitle = "", Keywords = "finger right most moved"), Category = "Leap Interface Event")
	void LeapLeftMostFingerMoved(UFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeapFrontFingerTouch", CompactNodeTitle = "", Keywords = "finger touched"), Category = "Leap Interface Event")
	void LeapFrontFingerTouch(UFinger* finger);		//emitted only for frontmost finger, typically best use case

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FingerCountChanged", CompactNodeTitle = "", Keywords = "finger count"), Category = "Leap Interface Event")
	void FingerCountChanged(int32 count);

	//Gestures
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "GestureDetected", CompactNodeTitle = "", Keywords = "gesture detect"), Category = "Leap Interface Event")
	void GestureDetected(UGesture* gesture);

	//Help identifying
	virtual FString ToString();
};
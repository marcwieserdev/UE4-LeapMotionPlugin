 
#pragma once

#include "LeapHand.h"
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
	void LeapHandMoved(ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeftHandMoved", CompactNodeTitle = "", Keywords = "left hand moved"), Category = "Leap Interface Event")
	void LeapLeftHandMoved(ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "RightHandMoved", CompactNodeTitle = "", Keywords = "right hand moved"), Category = "Leap Interface Event")
	void LeapRightHandMoved(ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandGrabbed", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandGrabbed(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandGrabbing", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandGrabbing(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandReleased", CompactNodeTitle = "", Keywords = "hand released ungrab"), Category = "Leap Interface Event")
	void LeapHandReleased(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandPinched", CompactNodeTitle = "", Keywords = "hand pinch"), Category = "Leap Interface Event")
	void LeapHandPinched(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandPinching", CompactNodeTitle = "", Keywords = "hand grab"), Category = "Leap Interface Event")
	void LeapHandPinching(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandUnpinched", CompactNodeTitle = "", Keywords = "hand unpinch"), Category = "Leap Interface Event")
	void LeapHandUnpinched(float strength, ULeapHand* hand);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "HandCountChanged", CompactNodeTitle = "", Keywords = "hand count"), Category = "Leap Interface Event")
	void HandCountChanged(int32 count);

	//Fingers
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FingerMoved", CompactNodeTitle = "", Keywords = "finger moved"), Category = "Leap Interface Event")
	void LeapFingerMoved(ULeapFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FrontFingerMoved", CompactNodeTitle = "", Keywords = "finger front most moved"), Category = "Leap Interface Event")
	void LeapFrontMostFingerMoved(ULeapFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeftFingerMoved", CompactNodeTitle = "", Keywords = "finger left most moved"), Category = "Leap Interface Event")
	void LeapRightMostFingerMoved(ULeapFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "RightFingerMoved", CompactNodeTitle = "", Keywords = "finger right most moved"), Category = "Leap Interface Event")
	void LeapLeftMostFingerMoved(ULeapFinger* finger);

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "LeapFrontFingerTouch", CompactNodeTitle = "", Keywords = "finger touched"), Category = "Leap Interface Event")
	void LeapFrontFingerTouch(ULeapFinger* finger);		//emitted only for frontmost finger, typically best use case

	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "FingerCountChanged", CompactNodeTitle = "", Keywords = "finger count"), Category = "Leap Interface Event")
	void FingerCountChanged(int32 count);

	//Gestures - Only emits if enabled
	UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "GestureDetected", CompactNodeTitle = "", Keywords = "gesture detect"), Category = "Leap Interface Event")
	void GestureDetected(ULeapGesture* gesture);

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture circle detect"), Category = "Leap Interface Event")
	void CircleGestureDetected(ULeapCircleGesture* gesture);

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture key tap detect"), Category = "Leap Interface Event")
	void KeyTapGestureDetected(ULeapKeyTapGesture* gesture);

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture screen tap detect"), Category = "Leap Interface Event")
	void ScreenTapGestureDetected(ULeapScreenTapGesture* gesture);

	UFUNCTION(BlueprintImplementableEvent, meta = (Keywords = "gesture swipe detect"), Category = "Leap Interface Event")
	void SwipeGestureDetected(ULeapSwipeGesture* gesture);

	//Images - Only emits if enabled
	UFUNCTION(BlueprintImplementableEvent, Category = "Leap Interface Event")
	void RawImageReceived(UTexture2D* texture, ULeapImage* image);

	//Help identifying
	virtual FString ToString();
};
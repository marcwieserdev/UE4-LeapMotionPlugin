#pragma once

#include "LeapMotionPrivatePCH.h"
#include "Gesture.generated.h"


UENUM(BlueprintType)
enum LeapGestureType
{
	GESTURE_TYPE_INVALID,
	GESTURE_TYPE_SWIPE,
	GESTURE_TYPE_CIRCLE,
	GESTURE_TYPE_SCREEN_TAP,
	GESTURE_TYPE_KEY_TAP
};

UENUM(BlueprintType)
enum LeapGestureState
{
	GESTURE_STATE_INVALID,
	GESTURE_STATE_START,
	GESTURE_STATE_UPDATE,
	GESTURE_STATE_STOP,
};

UCLASS(BlueprintType)
class UGesture : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UGesture();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "duration", CompactNodeTitle = "", Keywords = "duration"), Category = Leap)
	float Duration() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "durationSeconds", CompactNodeTitle = "", Keywords = "duration seconds"), Category = Leap)
	float DurationSeconds() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle = "", Keywords = "frame"), Category = Leap)
	class ULeapFrame* Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hands", CompactNodeTitle = "", Keywords = "hands"), Category = Leap)
	class UHandList* Hands();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "id", CompactNodeTitle = "", Keywords = "id"), Category = Leap)
	int32 Id();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "pointables", CompactNodeTitle = "", Keywords = "pointables"), Category = Leap)
	class UPointableList* Pointables() ;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "state", CompactNodeTitle = "", Keywords = "state"), Category = Leap)
	LeapGestureState State();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "type", CompactNodeTitle = "", Keywords = "type"), Category = Leap)
	LeapGestureType Type();

	bool operator!=(const UGesture &rhs) const;
	bool operator==(const UGesture &rhs) const;

	void setGesture(const Leap::Gesture &Gesture);
private:
	Leap::Gesture _gesture;
};
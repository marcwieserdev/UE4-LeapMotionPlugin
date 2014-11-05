#pragma once

#include "LeapMotionPublicPCH.h"
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

//Used for cardinal directions
UENUM(BlueprintType)
enum LeapPluginDirection
{
	DIRECTION_NONE,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_AWAY,
	DIRECTION_TOWARD,
};

UCLASS(BlueprintType)
class UGesture : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UGesture();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	float DurationSeconds;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle = "", Keywords = "frame"), Category = "Leap Gesture")
	class ULeapFrame* Frame();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hands", CompactNodeTitle = "", Keywords = "hands"), Category = "Leap Gesture")
	class UHandList* Hands();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	bool IsValid;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "pointables", CompactNodeTitle = "", Keywords = "pointables"), Category = "Leap Gesture")
	class UPointableList* Pointables();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	TEnumAsByte<LeapGestureState> State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture")
	TEnumAsByte<LeapGestureType> Type;

	bool operator!=(const UGesture &rhs) const;
	bool operator==(const UGesture &rhs) const;

	void setGesture(const class Leap::Gesture &Gesture);

private:
	class PrivateGesture* _private;
};
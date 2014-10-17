#pragma once

#include "LeapMotionPrivatePCH.h"
#include "GestureList.generated.h"

UCLASS(BlueprintType)
class UGestureList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UGestureList();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	bool IsEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	int32 Count;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "[]", Keywords = "get index"), Category = "Leap Gesture List")
	class UGesture *getIndex(int32 index);

	UGesture* operator[](int index);

	void setGestureList(const Leap::GestureList &gesturelist);

private:
	Leap::GestureList _gestures;
};
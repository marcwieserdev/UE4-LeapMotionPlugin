#pragma once

#include "LeapMotionPrivatePCH.h"
#include "GestureList.generated.h"

UCLASS(BlueprintType)
class UGestureList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UGestureList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count length"), Category = Leap)
	int32 Count();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = Leap)
	class UGesture *getIndex(int32 index);

	UGesture* operator[](int index);

	void setGestureList(const Leap::GestureList &gesturelist);

private:
	Leap::GestureList _gestures;
};
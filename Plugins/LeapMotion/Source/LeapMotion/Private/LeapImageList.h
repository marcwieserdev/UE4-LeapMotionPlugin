#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapImageList.generated.h"

UCLASS(BlueprintType)
class ULeapImageList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImageList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count length"), Category = Leap)
	int32 Count();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = Leap)
	class ULeapImage* getIndex(int32 index);

	ULeapImage* operator[](int index);

	void setLeapImageList(const Leap::ImageList &LeapImageList);

private:
	Leap::ImageList _leapImages;
};
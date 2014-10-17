#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapImageList.generated.h"

UCLASS(BlueprintType)
class ULeapImageList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImageList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = "Leap Image List")
	bool isEmpty() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image List")
	int32 Count;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = "Leap Image List")
	class ULeapImage* getIndex(int32 index);

	ULeapImage* operator[](int index);

	void setLeapImageList(const Leap::ImageList &LeapImageList);

private:
	Leap::ImageList _leapImages;
};
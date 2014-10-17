#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapImageList.generated.h"

UCLASS(BlueprintType)
class ULeapImageList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapImageList();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image List")
	bool IsEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Image List")
	int32 Count;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = "Leap Image List")
	class ULeapImage* getIndex(int32 index);

	ULeapImage* operator[](int index);

	void setLeapImageList(const Leap::ImageList &LeapImageList);

private:
	Leap::ImageList _leapImages;
	ULeapImage* _indexImage1;
	ULeapImage* _indexImage2;
};
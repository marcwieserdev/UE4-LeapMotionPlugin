#pragma once

#include "LeapMotionPublicPCH.h"
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

	void setLeapImageList(const class Leap::ImageList &LeapImageList);

	virtual void CleanupRootReferences();

private:
	class PrivateLeapImageList* _private;
};
#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapGestureList.generated.h"

UCLASS(BlueprintType)
class ULeapGestureList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapGestureList();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	bool IsEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Gesture List")
	int32 Count;
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "[]", Keywords = "get index"), Category = "Leap Gesture List")
	class ULeapGesture *getIndex(int32 index);

	ULeapGesture* operator[](int index);

	void setGestureList(const class Leap::GestureList &gesturelist);

	virtual void CleanupRootReferences();

private:
	class PrivateGestureList* _private;
};
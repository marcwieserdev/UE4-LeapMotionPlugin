#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapHandList.generated.h"

UCLASS(BlueprintType)
class ULeapHandList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapHandList();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand List")
	bool IsEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getFrontmost", CompactNodeTitle = "", Keywords = "get frontmost"), Category = "Leap Hand List")
	class ULeapHand* Frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getLeftmost", CompactNodeTitle = "", Keywords = "get leftmost"), Category = "Leap Hand List")
	class ULeapHand* Leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getRightmost", CompactNodeTitle = "", Keywords = "get rightmost"), Category = "Leap Hand List")
	class ULeapHand* Rightmost();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = "Leap Hand List")
	class ULeapHand* getIndex(int32 index);

	void setHandList(const class Leap::HandList &handlist);

	virtual void CleanupRootReferences();

private:
	class PrivateHandList* _private;
};
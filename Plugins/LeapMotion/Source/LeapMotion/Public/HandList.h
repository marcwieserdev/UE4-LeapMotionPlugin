#pragma once

#include "LeapMotionPublicPCH.h"
#include "HandList.generated.h"

UCLASS(BlueprintType)
class UHandList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UHandList();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand List")
	bool IsEmpty;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Hand List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getFrontmost", CompactNodeTitle = "", Keywords = "get frontmost"), Category = "Leap Hand List")
	class UHand* Frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getLeftmost", CompactNodeTitle = "", Keywords = "get leftmost"), Category = "Leap Hand List")
	class UHand* Leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getRightmost", CompactNodeTitle = "", Keywords = "get rightmost"), Category = "Leap Hand List")
	class UHand* Rightmost();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = "Leap Hand List")
	class UHand* getIndex(int32 index);

	void setHandList(const class Leap::HandList &handlist);

private:
	class PrivateHandList* _private;
};
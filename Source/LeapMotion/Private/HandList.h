#pragma once

#include "LeapMotionPrivatePCH.h"
#include "HandList.generated.h"

UCLASS(BlueprintType)
class UHandList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UHandList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count lenght"), Category = Leap)
	int32 Count();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost front hand"), Category = Leap)
	class UHand *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost left hand"), Category = Leap)
	class UHand *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost right hand"), Category = Leap)
	class UHand *rightmost();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getIndex", CompactNodeTitle = "", Keywords = "get index"), Category = Leap)
	class UHand *getIndex(int32 index);

	void setHandList(const Leap::HandList &handlist);
private:
	Leap::HandList _hands;
};
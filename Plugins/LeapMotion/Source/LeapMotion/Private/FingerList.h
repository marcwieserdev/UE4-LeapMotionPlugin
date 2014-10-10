#pragma once

#include "LeapMotionPrivatePCH.h"
#include "FingerList.generated.h"

UCLASS(BlueprintType)
class UFingerList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UFingerList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = Leap)
	UFingerList *append(const UFingerList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count"), Category = Leap)
	int32 Count() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = Leap)
	UFingerList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = Leap)
	class UFinger *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = Leap)
	class UFinger *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = Leap)
	class UFinger *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = Leap)
	class UFinger *rightmost();

	void setFingerList(const Leap::FingerList &pointables);
private:
	Leap::FingerList _fingers;
};
#pragma once

#include "LeapMotionPrivatePCH.h"
#include "PointableList.generated.h"

UCLASS(BlueprintType)
class UPointableList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UPointableList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = Leap)
	UPointableList *append(const UPointableList *list);

	/*UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = Leap)
	UPointableList *appendFingers(const class UFingerList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = Leap)
	UPointableList *appendTools(const class UToolsList *list);*/

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count"), Category = Leap)
	int32 Count() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = Leap)
	UPointableList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = Leap)
	class UPointable *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = Leap)
	class UPointable *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = Leap)
	class UPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = Leap)
	class UPointable *rightmost();

	void setPointableList(const Leap::PointableList &pointables);
private:
	Leap::PointableList _pointables;
};
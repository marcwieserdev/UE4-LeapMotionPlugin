#pragma once

#include "LeapMotionPrivatePCH.h"
#include "ToolList.generated.h"

UCLASS(BlueprintType)
class UToolList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UToolList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = Leap)
	UToolList *append(const UToolList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count"), Category = Leap)
	int32 Count() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = Leap)
	class UTool *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = Leap)
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = Leap)
	class UTool *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = Leap)
	class UPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = Leap)
	class UTool *rightmost();

	void setToolList(const Leap::ToolList &tools);
private:
	Leap::ToolList _tools;
	UTool* _leftmost;
	UTool* _rightmost;
	UTool* _frontmost;
	UPointable* _pointableById;
};
#pragma once

#include "LeapMotionPublicPCH.h"
#include "ToolList.generated.h"

UCLASS(BlueprintType)
class UToolList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UToolList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Tool List")
	UToolList *append(const UToolList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count"), Category = "Leap Tool List")
	int32 Count() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Tool List")
	class UTool *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = "Leap Tool List")
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Tool List")
	class UTool *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Tool List")
	class UPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Tool List")
	class UTool *rightmost();

	void setToolList(const class Leap::ToolList &tools);

private:
	class PrivateToolList* _private;
};
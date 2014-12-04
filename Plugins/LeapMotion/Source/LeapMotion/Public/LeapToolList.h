#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapToolList.generated.h"

UCLASS(BlueprintType)
class ULeapToolList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapToolList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Tool List")
	ULeapToolList *append(const ULeapToolList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "count", CompactNodeTitle = "", Keywords = "count"), Category = "Leap Tool List")
	int32 Count() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Tool List")
	class ULeapTool *frontmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isEmpty", CompactNodeTitle = "", Keywords = "is empty"), Category = "Leap Tool List")
	bool isEmpty() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Tool List")
	class ULeapTool *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Tool List")
	class ULeapPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Tool List")
	class ULeapTool *rightmost();

	void setToolList(const class Leap::ToolList &tools);
	const Leap::ToolList* toolList();

	virtual void CleanupRootReferences();

private:
	class PrivateToolList* _private;
};
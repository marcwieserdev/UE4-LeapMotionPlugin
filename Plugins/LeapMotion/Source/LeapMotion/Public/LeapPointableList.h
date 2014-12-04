#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapPointableList.generated.h"

UCLASS(BlueprintType)
class ULeapPointableList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapPointableList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* append(class ULeapPointableList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "appendFingers", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* appendFingers(class ULeapFingerList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "appendTools", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	ULeapPointableList* appendTools(class ULeapToolList *list);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = "Leap Pointable List")
	ULeapPointableList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Pointable List")
	class ULeapPointable *frontmost();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	bool IsEmpty;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Pointable List")
	class ULeapPointable *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Pointable List")
	class ULeapPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Pointable List")
	class ULeapPointable *rightmost();

	void setPointableList(const class Leap::PointableList &pointables);

	virtual void CleanupRootReferences();

private:
	class PrivatePointableList* _private;
};
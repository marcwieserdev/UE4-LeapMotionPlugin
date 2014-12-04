#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapFingerList.generated.h"

UCLASS(BlueprintType)
class ULeapFingerList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapFingerList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Finger List")
	ULeapFingerList *append(const ULeapFingerList *list);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = "Leap Finger List")
	ULeapFingerList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Finger List")
	class ULeapFinger *frontmost();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger List")
	bool IsEmpty;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Finger List")
	class ULeapFinger *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Finger List")
	class ULeapFinger *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Finger List")
	class ULeapFinger *rightmost();

	void setFingerList(const class Leap::FingerList &pointables);
	Leap::FingerList* fingerList();

	virtual void CleanupRootReferences();

private:
	class PrivateFingerList* _private;
};
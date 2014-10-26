#pragma once

#include "LeapMotionPublicPCH.h"
#include "PointableList.generated.h"

UCLASS(BlueprintType)
class UPointableList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UPointableList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	UPointableList* append(class UPointableList *list);

	/*UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	UPointableList* appendFingers(class UFingerList *list);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Pointable List")
	UPointableList* appendTools(class UToolList *list);*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = "Leap Pointable List")
	UPointableList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Pointable List")
	class UPointable *frontmost();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Pointable List")
	bool IsEmpty;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Pointable List")
	class UPointable *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Pointable List")
	class UPointable *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Pointable List")
	class UPointable *rightmost();

	void setPointableList(const class Leap::PointableList &pointables);

private:
	class PrivatePointableList* _private;
};
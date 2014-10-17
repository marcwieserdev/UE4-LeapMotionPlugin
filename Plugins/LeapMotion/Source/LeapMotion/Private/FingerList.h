#pragma once

#include "LeapMotionPrivatePCH.h"
#include "FingerList.generated.h"

UCLASS(BlueprintType)
class UFingerList : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~UFingerList();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "append", CompactNodeTitle = "", Keywords = "append"), Category = "Leap Finger List")
	UFingerList *append(const UFingerList *list);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger List")
	int32 Count;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "extended", CompactNodeTitle = "", Keywords = "extended"), Category = "Leap Finger List")
	UFingerList *extended();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frontmost", CompactNodeTitle = "", Keywords = "frontmost"), Category = "Leap Finger List")
	class UFinger *frontmost();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leap Finger List")
	bool IsEmpty;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "leftmost", CompactNodeTitle = "", Keywords = "leftmost"), Category = "Leap Finger List")
	class UFinger *leftmost();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointableById", CompactNodeTitle = "[]", Keywords = "get pointable by id"), Category = "Leap Finger List")
	class UFinger *getPointableById(int32 id);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "rightmost", CompactNodeTitle = "", Keywords = "rightmost"), Category = "Leap Finger List")
	class UFinger *rightmost();

	void setFingerList(const Leap::FingerList &pointables);
private:
	Leap::FingerList _fingers;
	UFinger* _frontmost;
	UFinger* _leftmost;
	UFinger* _rightmost;
	UFinger* _pointableById;
};
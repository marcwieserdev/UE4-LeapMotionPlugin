#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapFrame.generated.h"

UCLASS(BlueprintType)
class ULeapFrame : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	//ULeapFrame(const ULeapFrame &cpy);
	~ULeapFrame();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getHands", CompactNodeTitle = "", Keywords = "get hands"), Category = Leap)
	class UHandList *hands();

	void setFrame(Leap::Controller &leap, int history = 0);
	void setFrame(const Leap::Frame &frame);

private:
	Leap::Frame _frame;
};
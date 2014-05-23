#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapFrame.generated.h"

UCLASS(BlueprintType)
class ULeapFrame : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	~ULeapFrame();
	
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "currentFramePerSecond", CompactNodeTitle = "FPS", Keywords = "get frame per second"), Category = Leap)
	float currentFramePerSecond() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isValid", CompactNodeTitle = "", Keywords = "is valid"), Category = Leap)
	bool IsValid() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getHands", CompactNodeTitle = "", Keywords = "get hands"), Category = Leap)
	class UHandList *hands();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getFinger", CompactNodeTitle = "", Keywords = "get fingers"), Category = Leap)
	class UFingerList *fingers();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getTools", CompactNodeTitle = "", Keywords = "get tools"), Category = Leap)
	class UToolList *tools();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getPointables", CompactNodeTitle = "", Keywords = "get pointables"), Category = Leap)
	class UPointableList *pointables();

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getTimestamp", CompactNodeTitle = "", Keywords = "get timestamp"), Category = Leap)
	int64 TimeStamp() const;

	void setFrame(Leap::Controller &leap, int history = 0);
	void setFrame(const Leap::Frame &frame);
	const Leap::Frame &getFrame() const;
private:
	Leap::Frame _frame;
};
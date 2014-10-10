#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapFrame.h"
#include "LeapController.generated.h"

UCLASS(ClassGroup=VR, meta=(BlueprintSpawnableComponent))
class ULeapController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	~ULeapController();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Is Connected", CompactNodeTitle = "", Keywords = "is connected"), Category = Leap)
	bool isConnected() const;

	UFUNCTION(BlueprintCallable, Category = Leap)
	class ULeapFrame *getFrame(int32 history);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hasFocus", CompactNodeTitle = "", Keywords = "has Focus"), Category = Leap)
	bool hasFocus() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isServiceConnected", CompactNodeTitle = "", Keywords = "is service connected"), Category = Leap)
	bool isServiceConnected() const;

	const Leap::Controller &getData() const;

private:
	Leap::Controller	_leap;
};
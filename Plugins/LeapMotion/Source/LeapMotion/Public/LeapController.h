#pragma once
#include "LeapMotionPublicPCH.h"
#include "LeapGesture.h"
#include "LeapController.generated.h"

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class ULeapController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	~ULeapController();
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Is Connected", CompactNodeTitle = "", Keywords = "is connected"), Category = "Leap Controller")
	bool IsConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Get Frame", CompactNodeTitle = "Frame", Keywords = "get frame"), Category = "Leap Controller")
	class ULeapFrame* Frame(int32 history);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hasFocus", CompactNodeTitle = "", Keywords = "has Focus"), Category = "Leap Controller")
	bool HasFocus() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isServiceConnected", CompactNodeTitle = "", Keywords = "is service connected"), Category = "Leap Controller")
	bool IsServiceConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "optimizeForHMD", Keywords = "optimize hmd facing top set policy"), Category = "Leap Controller")
	void OptimizeForHMD(bool useTopdown = false, bool autoRotate = true, bool autoShift = true);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableImageSupport", Keywords = "use allow images set policy"), Category = "Leap Controller")
	void EnableImageSupport(bool allowImages = true, bool emitImageEvents = true);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableGesture", Keywords = "enable gesture"), Category = "Leap Controller")
	void EnableGesture(enum LeapGestureType type, bool enable = true);

	//Leap Event Interface forwarding, automatically set since 0.6.2, available for event redirection
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "setDelegate", CompactNodeTitle = "", Keywords = "set delegate self"), Category = "Leap Interface")
	void SetInterfaceDelegate(UObject* newDelegate);

private:
	class LeapControllerPrivate* _private;
	void InterfaceEventTick(float deltaTime);
};
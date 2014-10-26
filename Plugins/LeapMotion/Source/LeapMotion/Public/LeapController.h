#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapEventInterface.h"
#include "LeapController.generated.h"

//Forward declare namespace so public is not exposed to Leap header
namespace Leap
{
	class Arm;
	class Bone;
	class CircleGesture;
	class Controller;
	class Finger;
	class FingerList;
	class Gesture;
	class GestureList;
	class Hand;
	class HandList;
	class InteractionBox;
	class KeyTapGesture;
	class Frame;
	class Image;
	class ImageList;
	class Pointable;
	class PointableList;
	class ScreenTapGesture;
	class SwipeGesture;
	class Tool;
	class ToolList;
}

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class ULeapController : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	~ULeapController();
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Is Connected", CompactNodeTitle = "", Keywords = "is connected"), Category = "Leap Controller")
	bool isConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "Get Frame", CompactNodeTitle = "Frame", Keywords = "get frame"), Category = "Leap Controller")
	class ULeapFrame* Frame(int32 history);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hasFocus", CompactNodeTitle = "", Keywords = "has Focus"), Category = "Leap Controller")
	bool hasFocus() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isServiceConnected", CompactNodeTitle = "", Keywords = "is service connected"), Category = "Leap Controller")
	bool isServiceConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "optimizeForHMD", Keywords = "optimize hmd facing top set policy"), Category = "Leap Controller")
	void optimizeForHMD(bool useTopdown = false, bool autoRotate = true, bool autoShift = true);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableImageSupport", Keywords = "use allow images set policy"), Category = "Leap Controller")
	void enableImageSupport(bool allowImages = true);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableGesture", Keywords = "optimize hmd facing top"), Category = "Leap Controller")
	void enableGesture(enum LeapGestureType type, bool enable = true);

	//Leap Event Interface forwarding, automatically set since 0.6.2, available for event redirection
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "setDelegate", CompactNodeTitle = "", Keywords = "set delegate self"), Category = "Leap Interface")
	void SetInterfaceDelegate(UObject* newDelegate);

private:
	class LeapControllerPrivate* _private;
	void InterfaceEventTick(float deltaTime);
};
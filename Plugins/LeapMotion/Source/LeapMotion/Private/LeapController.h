#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"
#include <vector>
#include "LeapController.generated.h"

//Todo: 
//-change functions into read-only properties to reduce exec clutter. Can easily remove all const to stop call target bp errors.

//Used for Reliable State Tracking
struct LeapHandStateData{
	bool grabbed;
	bool pinched;
	int32 fingerCount;
	int32 id;
};

class LeapStateData{
public:
	bool hasStateForId(int32 hId, LeapHandStateData& state);
	LeapHandStateData stateForId(int32 hId);
	void setStateForId(LeapHandStateData handState, int32 hId);

	std::vector<LeapHandStateData> handStates;
	int32 handCount;
};

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

	//Frame
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "getFrame", CompactNodeTitle = "", Keywords = "get frame"), Category = "Leap Controller")
	class ULeapFrame *getFrame(int32 history);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hasFocus", CompactNodeTitle = "", Keywords = "has Focus"), Category = "Leap Controller")
	bool hasFocus() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isServiceConnected", CompactNodeTitle = "", Keywords = "is service connected"), Category = "Leap Controller")
	bool isServiceConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "optimizeForHMD", Keywords = "optimize hmd facing top set policy"), Category = "Leap Controller")
	void optimizeForHMD(bool useTopdown = false, bool autoRotate = true, bool autoShift = true);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableImageSupport", Keywords = "use allow images set policy"), Category = "Leap Controller")
	void enableImageSupport(bool allowImages);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableGesture", CompactNodeTitle = "", Keywords = "optimize hmd facing top"), Category = "Leap Controller")
	void enableGesture(enum LeapGestureType type, bool enable = true);

	const Leap::Controller &getData() const;

	//Leap Event Interface forwarding, automatically set since 0.6.2, available for event redirection
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "setDelegate", CompactNodeTitle = "", Keywords = "set delegate self"), Category = "Leap Interface")
	void SetInterfaceDelegate(UObject* newDelegate);

private:
	Leap::Controller	_leap;
	UObject* _interfaceDelegate;
	bool _optimizeForHMD;
	bool _allowImages;	
	LeapStateData _pastState;

	Leap::Controller::PolicyFlag buildPolicyFromBools();
	void InterfaceEventTick(float deltaTime);
};
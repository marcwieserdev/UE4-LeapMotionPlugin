#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"
#include <vector>
#include "LeapController.generated.h"

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

	//Frame
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "frame", CompactNodeTitle = "", Keywords = "frame"), Category = Leap)
	class ULeapFrame *getFrame(int32 history);

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "hasFocus", CompactNodeTitle = "", Keywords = "has Focus"), Category = Leap)
	bool hasFocus() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "isServiceConnected", CompactNodeTitle = "", Keywords = "is service connected"), Category = Leap)
	bool isServiceConnected() const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "optimizeForHMD", Keywords = "optimize hmd facing top"), Category = Leap)
	void optimizeForHMD(bool useTopdown = false, bool autoRotate = true, bool autoShift = true) const;

	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "enableGesture", CompactNodeTitle = "", Keywords = "optimize hmd facing top"), Category = Leap)
	void enableGesture(enum LeapGestureType type, bool enable = true);

	const Leap::Controller &getData() const;

	//Leap Event Interface forwarding
	UFUNCTION(BlueprintCallable, meta = (FriendlyName = "setDelegate", CompactNodeTitle = "", Keywords = "set delegate self"), Category = "Leap Interface")
	void SetInterfaceDelegate(UObject* newDelegate);

private:
	Leap::Controller	_leap;
	UObject* _interfaceDelegate;
	LeapStateData _pastState;

	void InterfaceEventTick(float deltaTime);
};
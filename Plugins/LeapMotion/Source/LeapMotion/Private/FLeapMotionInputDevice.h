#pragma once

#include "LeapMotionPrivatePCH.h"
#include "IInputDevice.h"

/**
* Stores raw controller data and custom toggles
*/
struct LeapControllerData
{
	//Reference to the Leap Controller base
	Leap::Controller LeapController;

	//Public custom controller toggles
	bool bAllowImageEvents = false;
	bool bOptimizeForHMD = false;
	bool bUseGammaCorrection = false;
	bool bImageEventsEnabled = false;
	bool bUseMountOffset = true;
};

class FLeapMotionInputDevice : public IInputDevice
{
public:
	FLeapMotionInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& MessageHandler);

	void CustomInitializer();

	/** Tick the interface (e.g. check for new controllers) */
	virtual void Tick(float DeltaTime) override;

	/** Poll for controller state and send events if needed */
	virtual void SendControllerEvents() override;

	/** Set which MessageHandler will get the events from SendControllerEvents. */
	virtual void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) override;

	/** Exec handler to allow console commands to be passed through for debugging */
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	/** IForceFeedbackSystem pass through functions **/
	virtual void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	virtual void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override;

	virtual ~FLeapMotionInputDevice();

	TSharedRef< FGenericApplicationMessageHandler > MessageHandler;

	/** Main Controller data and settings reference*/
	LeapControllerData ControllerData;
	
	void AddEventDelegate(UObject* EventDelegate);
	void RemoveEventDelegate(UObject* EventDelegate);

private:
	//Private UProperties
	void ClearReferences(UObject* object);
	class ULeapBaseObject* PRoot = nullptr;
	class ULeapHand* PEventHand = nullptr;
	class ULeapFinger* PEventFinger = nullptr;
	class ULeapGesture* PEventGesture = nullptr;
	class ULeapCircleGesture* PEventCircleGesture = nullptr;
	class ULeapKeyTapGesture* PEventKeyTapGesture = nullptr;
	class ULeapScreenTapGesture* PEventScreenTapGesture = nullptr;
	class ULeapSwipeGesture* PEventSwipeGesture = nullptr;
	class ULeapImage* PEventImage1 = nullptr;
	class ULeapImage* PEventImage2 = nullptr;

	class LeapStateData* PastState;
	TArray<UObject*> EventDelegates;

	//Private utility methods
	void CallFunctionOnDelegates(TFunction< void(UObject*)> InFunction);	//lambda multi-cast convenience wrapper
	bool EmitKeyUpEventForKey(FKey Key, int32 User, bool Repeat);
	bool EmitKeyDownEventForKey(FKey Key, int32 User, bool Repeat);
	bool EmitAnalogInputEventForKey(FKey Key, float Value, int32 User, bool Repeat);
	bool HandClosed(float Strength);
	bool HandPinched(float Strength);
	bool HandForId(int32 CheckId, Leap::HandList Hands, Leap::Hand& ReturnHand);
};
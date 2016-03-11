#include "LeapMotionPrivatePCH.h"
#include "FLeapMotionInputDevice.h"

#define LOCTEXT_NAMESPACE "LeapPlugin"
#define PLUGIN_VERSION "2.0.0"

void FLeapMotionPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	// Custom module-specific init can go here.

	// IMPORTANT: This line registers our input device module with the engine.
	//	      If we do not register the input device module with the engine,
	//	      the engine won't know about our existence. Which means 
	//	      CreateInputDevice never gets called, which means the engine
	//	      will never try to poll for events from our custom input device.
	IModularFeatures::Get().RegisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}

void FLeapMotionPlugin::ShutdownModule()
{
	// Unregister our input device module
	IModularFeatures::Get().UnregisterModularFeature(IInputDeviceModule::GetModularFeatureName(), this);
}


LeapControllerData* FLeapMotionPlugin::ControllerData()
{
	if (bActive) 
	{
		return &(LeapInputDevice->ControllerData);
	}
	else
	{
		return nullptr;
	}
}

void FLeapMotionPlugin::AddEventDelegate(UObject* EventDelegate)
{
	LeapInputDevice->AddEventDelegate(EventDelegate);
}


void FLeapMotionPlugin::RemoveEventDelegate(UObject* EventDelegate)
{
	LeapInputDevice->RemoveEventDelegate(EventDelegate);
}

TSharedPtr< class IInputDevice > FLeapMotionPlugin::CreateInputDevice(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	UE_LOG(LeapPluginLog, Log, TEXT("CreateInputDevice LeapPlugin version %s"), TEXT(PLUGIN_VERSION));

	//Expose all of our input mapping keys to the engine
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftPinch, LOCTEXT("LeapLeftPinch", "Leap Left Pinch"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftGrab, LOCTEXT("LeapLeftGrab", "Leap Left Grab"), FKeyDetails::GamepadKey));

	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftPalmPitch, LOCTEXT("LeapLeftPalmPitch", "Leap Left Palm Pitch"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftPalmYaw, LOCTEXT("LeapLeftPalmYaw", "Leap Left Palm Yaw"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapLeftPalmRoll, LOCTEXT("LeapLeftPalmRoll", "Leap Left Palm Roll"), FKeyDetails::FloatAxis));

	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapRightPinch, LOCTEXT("LeapRightPinch", "Leap Right Pinch"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapRightGrab, LOCTEXT("LeapRightGrab", "Leap Right Grab"), FKeyDetails::GamepadKey));

	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapRightPalmPitch, LOCTEXT("LeapRightPalmPitch", "Leap Right Palm Pitch"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapRightPalmYaw, LOCTEXT("LeapRightPalmYaw", "Leap Right Palm Yaw"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(EKeysLeap::LeapRightPalmRoll, LOCTEXT("LeapRightPalmRoll", "Leap Right Palm Roll"), FKeyDetails::FloatAxis));

	FLeapMotionPlugin::LeapInputDevice = MakeShareable(new FLeapMotionInputDevice(InMessageHandler));

	bActive = true;

	return TSharedPtr< class IInputDevice >(LeapInputDevice);
}

IMPLEMENT_MODULE(FLeapMotionPlugin, LeapMotion)

#undef LOCTEXT_NAMESPACE
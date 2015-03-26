#include "LeapMotionPrivatePCH.h"

#define LOCTEXT_NAMESPACE "LeapPlugin"
#define PLUGIN_VERSION "0.9.2"

void FLeapMotion::StartupModule()
{
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

	UE_LOG(LeapPluginLog, Log, TEXT("Using LeapPlugin version %s"), TEXT(PLUGIN_VERSION));
}

void FLeapMotion::ShutdownModule()
{
    
}

Leap::Controller* FLeapMotion::Controller()
{
	return &LeapController;
}

IMPLEMENT_MODULE(FLeapMotion, LeapMotion)

#undef LOCTEXT_NAMESPACE
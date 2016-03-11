#pragma once

#include "LeapMotionPrivatePCH.h"
#include "LeapBlueprintFunctionLibrary.h"

ULeapBlueprintFunctionLibrary::ULeapBlueprintFunctionLibrary(const class FObjectInitializer& Initializer)
	: Super(Initializer)
{

}

void ULeapBlueprintFunctionLibrary::GetHMDFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees)
{
	float HFOV, VFOV;
	GEngine->HMDDevice->GetFieldOfView(HFOV, VFOV);
	OutHFOVInDegrees = HFOV;
	OutVFOVInDegrees = VFOV;
}

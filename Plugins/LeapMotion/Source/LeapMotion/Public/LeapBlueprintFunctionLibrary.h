// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LeapBlueprintFunctionLibrary.generated.h"

/**
* Useful global blueprint functions for Leap Motion
*/
UCLASS()
class ULeapBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/**
	* Wrapper function for IHeadMountedDisplay::GetFieldOfView for blueprint use
	*/
	UFUNCTION(BlueprintPure, Category = "Leap Motion Functions")
	static void GetHMDFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees);
};
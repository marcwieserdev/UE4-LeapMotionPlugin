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
	* Enable warping the event driven hand tracking data by the difference in latest Head Mounted Display transform
	* and the transform when the data was sampled.
	*
	* @param True	if you wish to enable timewarp. Defaults value is true
	* @param Factor		value 0-1.f that the timewarp should apply
	*/
	UFUNCTION(BlueprintCallable, Category = "Leap Motion Functions")
	static void EnableTimeWarp(bool Enable = true, float Factor = 1.f, float Tween = 1.f);

	/**
	* Wrapper function for IHeadMountedDisplay::GetFieldOfView for blueprint use
	*
	* @param OutHFOVInDegrees	Horizontal field of view in degrees
	* @param OutVFOVInDegrees	Vertical field of view in degrees
	*
	*/
	UFUNCTION(BlueprintPure, Category = "Leap Motion Functions")
	static void GetHMDFieldOfView(float& OutHFOVInDegrees, float& OutVFOVInDegrees);

	/**
	* Leap time warp Factor useful for adjusting timewarp
	*
	* @param OutFactor				value 0-1.f that the timewarp should apply
	* @param OutTimeWarpAmountMs	The amount of time the leap motion time warps in ms
	*/
	UFUNCTION(BlueprintPure, Category = "Leap Motion Functions")
	static void GetTimewarpStats(bool& OutEnabled, float& OutFactor, float& OutTimeWarpAmountMs);
};
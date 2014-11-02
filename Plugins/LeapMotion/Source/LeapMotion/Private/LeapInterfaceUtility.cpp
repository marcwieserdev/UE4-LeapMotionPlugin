#pragma once

#include "LeapMotionPrivatePCH.h"
#include "IHeadMountedDisplay.h"

DEFINE_LOG_CATEGORY(LeapPluginLog);
#define LEAP_TO_UE_SCALE 0.1f
#define UE_TO_LEAP_SCALE 10.f

//NB: localized variable for transforms
bool LeapShouldAdjustForFacing = false;
bool LeapShouldAdjustRotationForHMD = false;
bool LeapShouldAdjustPositionForHMD = false;

FVector adjustForLeapFacing(FVector in)
{
	FRotator rotation = FRotator(90.f, 0.f, 180.f);
	return FQuat(rotation).RotateVector(in);
}

FVector adjustForHMD(FVector in)
{
	if (GEngine->HMDDevice.IsValid())
	{
		FQuat orientationQuat;
		FVector position;
		GEngine->HMDDevice->GetCurrentOrientationAndPosition(orientationQuat, position);
		FVector out = orientationQuat.RotateVector(in);
		if (LeapShouldAdjustPositionForHMD)
			out += position;
		return out;
	}
	else
		return in;

}

//Conversion - use find and replace to change behavior
FVector convertLeapToUE(Leap::Vector leapVector)
{
	FVector vect = FVector(-leapVector.z, leapVector.x, leapVector.y);
	if (LeapShouldAdjustForFacing)
	{
		vect = adjustForLeapFacing(vect);
	}
	return vect;
}

FVector convertAndScaleLeapToUE(Leap::Vector leapVector)
{
	//Scale from mm to cm (ue default)
	FVector vect = FVector(-leapVector.z * LEAP_TO_UE_SCALE, leapVector.x * LEAP_TO_UE_SCALE, leapVector.y * LEAP_TO_UE_SCALE);

	//Front facing leap adjustments
	if (LeapShouldAdjustForFacing)
	{
		vect = adjustForLeapFacing(vect);
		if (LeapShouldAdjustRotationForHMD)
			vect = adjustForHMD(vect);
	}
	return vect;
}

Leap::Vector convertUEToLeap(FVector ueVector)
{
	return Leap::Vector(ueVector.Y, ueVector.Z, -ueVector.X);
}

Leap::Vector convertAndScaleUEToLeap(FVector ueVector)
{
	return Leap::Vector(ueVector.Y * UE_TO_LEAP_SCALE, ueVector.Z * UE_TO_LEAP_SCALE, -ueVector.X * UE_TO_LEAP_SCALE);
}

float scaleLeapToUE(float leapFloat)
{
	return leapFloat * LEAP_TO_UE_SCALE;	//mm->cm
}

float scaleUEToLeap(float ueFloat)
{
	return ueFloat * UE_TO_LEAP_SCALE;	//mm->cm
}

void LeapSetShouldAdjustForFacing(bool shouldRotate)
{
	LeapShouldAdjustForFacing = shouldRotate;
}

void LeapSetShouldAdjustForHMD(bool shouldRotate, bool shouldOffset)
{
	LeapShouldAdjustRotationForHMD = shouldRotate;
	LeapShouldAdjustPositionForHMD = shouldOffset;
}
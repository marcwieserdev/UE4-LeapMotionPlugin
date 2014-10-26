#pragma once

#include "LeapMotionPrivatePCH.h"
#include "IHeadMountedDisplay.h"

DEFINE_LOG_CATEGORY(LeapPluginLog);

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
	return (FVector(-leapVector.z, leapVector.x, leapVector.y));
}

FVector convertAndScaleLeapToUE(Leap::Vector leapVector)
{
	//Scale from mm to cm (ue default)
	FVector vect = FVector(-leapVector.z / 10.f, leapVector.x / 10.f, leapVector.y / 10.f);

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
	return Leap::Vector(ueVector.Y * 10.f, ueVector.Z * 10.f, -ueVector.X * 10.f);
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
#pragma once

#include "LeapMotionPrivatePCH.h"
#include "IHeadMountedDisplay.h"
#include "Gesture.h"

DEFINE_LOG_CATEGORY(LeapPluginLog);
#define LEAP_TO_UE_SCALE 0.1f
#define UE_TO_LEAP_SCALE 10.f
#define LEAP_MOUNT_OFFSET 8.f	//in cm (UE units) forming FVector(LEAP_MOUNT_OFFSET,0,0) forward vector

//NB: localized variable for transforms
bool LeapShouldAdjustForFacing = false;
bool LeapShouldAdjustRotationForHMD = false;
bool LeapShouldAdjustPositionForHMD = false;
bool LeapShouldAdjustForMountOffset = true;

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
		{
			if (LeapShouldAdjustForMountOffset)
				position += orientationQuat.RotateVector(FVector(LEAP_MOUNT_OFFSET, 0, 0));
			out += position;
		}
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

void LeapSetShouldAdjustForMountOffset(bool shouldAddOffset)
{
	LeapShouldAdjustForMountOffset = shouldAddOffset;
}

LeapPluginDirection cardinalDirection(FVector direction)
{
	float x = FMath::Abs(direction.X);
	float y = FMath::Abs(direction.Y);
	float z = FMath::Abs(direction.Z);

	//is cardinal in x?
	if (x >= y && x >= z)
	{
		if (direction.X < -0.5)
			return LeapPluginDirection::DIRECTION_TOWARD;
		else if (direction.X > 0.5)
			return LeapPluginDirection::DIRECTION_AWAY;
	}
	//is cardinal in y?
	else if (y >= x && y >= z)
	{
		if (direction.Y < -0.5)
			return LeapPluginDirection::DIRECTION_LEFT;
		else if (direction.Y > 0.5)
			return LeapPluginDirection::DIRECTION_RIGHT;
	}
	//is cardinal in z?
	else if (z >= x && z >= y)
	{
		if (direction.Z < -0.5)
			return LeapPluginDirection::DIRECTION_DOWN;
		else if (direction.Z > 0.5)
			return LeapPluginDirection::DIRECTION_UP;
	}
	
	//If we haven't returned by now, the direction is none
	return LeapPluginDirection::DIRECTION_NONE;
}

//Utility function used to debug address allocation - helped find the cdcdcdcd allocation error
void UtilityDebugAddress(void* pointer)
{
	const void * address = static_cast<const void*>(pointer);
	std::stringstream ss;
	ss << address;
	std::string name = ss.str();
	FString string(name.c_str());

	UE_LOG(LeapPluginLog, Warning, TEXT("Address: %s"), *string);
}
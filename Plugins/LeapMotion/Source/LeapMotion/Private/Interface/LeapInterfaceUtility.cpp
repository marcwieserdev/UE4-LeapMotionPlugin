#pragma once

#include "LeapMotionPrivatePCH.h"

//NB: localized variable for transforms
bool LeapShouldRotateVector = false;

FVector rotateForHMD(FVector in)
{
	FRotator rotation = FRotator(90.f, 0.f, 180.f);
	return FQuat(rotation).RotateVector(in);
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

	if (LeapShouldRotateVector)
		return rotateForHMD(vect);
	else
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





void LeapShouldRotateForHMD(bool shouldRotate)
{
	LeapShouldRotateVector = shouldRotate;
}
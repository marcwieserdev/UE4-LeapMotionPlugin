#pragma once

#include "LeapMotionPrivatePCH.h"

//Conversion - use find and replace to change behavior
FVector convertLeapToUE(Leap::Vector leapVector)
{
	return (FVector(-leapVector.z, leapVector.x, leapVector.y));
}
FVector convertAndScaleLeapToUE(Leap::Vector leapVector)
{
	//Scale from mm to cm (ue default)
	return (FVector(-leapVector.z / 10.f, leapVector.x / 10.f, leapVector.y / 10.f));
}
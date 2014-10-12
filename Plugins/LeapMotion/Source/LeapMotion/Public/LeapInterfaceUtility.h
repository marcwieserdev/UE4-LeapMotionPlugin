#pragma once

#include "LEAP/Leap.h"
#include "Core.h"

//Conversion
FVector convertLeapToUE(Leap::Vector leapVector);
FVector convertAndScaleLeapToUE(Leap::Vector leapVector);
Leap::Vector convertUEToLeap(FVector ueVector);
Leap::Vector convertAndScaleUEToLeap(FVector ueVector);

//HMD automation
void LeapShouldRotateForHMD(bool shouldRotate);

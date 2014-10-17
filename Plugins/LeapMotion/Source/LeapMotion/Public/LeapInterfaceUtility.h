#pragma once

#include "Leap.h"
#include "Core.h"

//Conversion
FVector convertLeapToUE(Leap::Vector leapVector);
FVector convertAndScaleLeapToUE(Leap::Vector leapVector);
Leap::Vector convertUEToLeap(FVector ueVector);
Leap::Vector convertAndScaleUEToLeap(FVector ueVector);

//HMD automation
void LeapSetShouldAdjustForFacing(bool shouldRotate);
void LeapSetShouldAdjustForHMD(bool shouldRotate, bool shouldOffset);

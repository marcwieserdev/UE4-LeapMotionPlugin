#pragma once

#include "LEAP/Leap.h"
#include "Core.h"

//Conversion
FVector convertLeapToUE(Leap::Vector leapVector);
FVector convertAndScaleLeapToUE(Leap::Vector leapVector);
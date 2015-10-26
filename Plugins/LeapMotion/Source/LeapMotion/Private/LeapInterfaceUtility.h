#pragma once

#include "Leap.h"
#include "Core.h"

DECLARE_LOG_CATEGORY_EXTERN(LeapPluginLog, Log, All);

//Rotation
FRotator CombineRotators(FRotator A, FRotator B);


//Conversion
//To ue
FVector convertLeapToUE(Leap::Vector leapVector);
FVector convertAndScaleLeapToUE(Leap::Vector leapVector);
FMatrix convertLeapBasisMatrix(Leap::Matrix leapMatrix);
FMatrix swapLeftHandRuleForRight(const FMatrix &ueMatrix);		//needed for all left hand basis which will be incorrect in ue format

//To leap
Leap::Vector convertUEToLeap(FVector ueVector);
Leap::Vector convertAndScaleUEToLeap(FVector ueVector);

float scaleLeapToUE(float leapFloat);
float scaleUEToLeap(float ueFloat);

//HMD automation
void LeapSetShouldAdjustForFacing(bool shouldRotate);
void LeapSetShouldAdjustForHMD(bool shouldRotate, bool shouldOffset);
void LeapSetShouldAdjustForMountOffset(bool shouldAddOffset);

//Convenience gesture determination
enum LeapBasicDirection basicDirection(FVector direction);

//Pointer debugging
void UtilityDebugAddress(void* pointer);
bool UtilityPointerIsValid(void* pointer);
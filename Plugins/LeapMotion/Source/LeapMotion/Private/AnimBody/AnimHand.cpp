#include "LeapMotionPrivatePCH.h"
#include "AnimHand.h"

UAnimHand::UAnimHand(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Thumb = PCIP.CreateDefaultSubobject<UAnimFinger>(this, TEXT("Thumb"));
	Index = PCIP.CreateDefaultSubobject<UAnimFinger>(this, TEXT("Index"));
	Middle = PCIP.CreateDefaultSubobject<UAnimFinger>(this, TEXT("Middle"));
	Ring = PCIP.CreateDefaultSubobject<UAnimFinger>(this, TEXT("Ring"));
	Pinky = PCIP.CreateDefaultSubobject<UAnimFinger>(this, TEXT("Pinky"));

	Wrist = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Wrist"));
	LowerArm = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("LowerArm"));
}

bool UAnimHand::Enabled()
{
	return Alpha == 1.f;
}

void UAnimHand::SetEnabled(bool enable)
{
	if (enable)
	{
		Alpha = 1.f;
	}
	else
	{
		Alpha = 0.f;
	}

	//Forward to every finger
	Thumb->SetEnabled(enable);
	Index->SetEnabled(enable);
	Middle->SetEnabled(enable);
	Ring->SetEnabled(enable);
	Pinky->SetEnabled(enable);

	//Arm/Wrist
	Wrist->SetEnabled(enable);
	LowerArm->SetEnabled(enable);
}

void UAnimHand::TranslateHand(FVector shift)
{
	//Shift all fingers
	Thumb->TranslateFinger(shift);
	Index->TranslateFinger(shift);
	Middle->TranslateFinger(shift);
	Ring->TranslateFinger(shift);
	Pinky->TranslateFinger(shift);

	//Arm/Wrist
	Wrist->TranslateBone(shift);
	LowerArm->TranslateBone(shift);
}

void UAnimHand::ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors)
{
	//Change Basis for all fingers
	Thumb->ChangeBasis(PreBase, PostBase, adjustVectors);
	Index->ChangeBasis(PreBase, PostBase, adjustVectors);
	Middle->ChangeBasis(PreBase, PostBase, adjustVectors);
	Ring->ChangeBasis(PreBase, PostBase, adjustVectors);
	Pinky->ChangeBasis(PreBase, PostBase, adjustVectors);

	//Arm/Wrist
	Wrist->ChangeBasis(PreBase, PostBase, adjustVectors);
	LowerArm->ChangeBasis(PreBase, PostBase, adjustVectors);
}

void UAnimHand::SetFromLeapHand(ULeapHand* leapHand)
{
	//Wrist/Arm
	Wrist->Orientation = leapHand->PalmOrientation;
	Wrist->Position = leapHand->Arm->WristPosition;

	LowerArm->Position = leapHand->Arm->ElbowPosition;
	LowerArm->Orientation = leapHand->Arm->Direction.Rotation();

	//Fingers
	ULeapFingerList* fingers = leapHand->Fingers();

	for (int i = 0; i < fingers->Count; i++)
	{
		ULeapFinger* finger = fingers->getPointableById(i);
		switch (finger->Type)
		{
		case FINGER_TYPE_THUMB:
			Thumb->SetFromLeapFinger(finger);
			break;
		case FINGER_TYPE_INDEX:
			Index->SetFromLeapFinger(finger);
			break;
		case FINGER_TYPE_MIDDLE:
			Middle->SetFromLeapFinger(finger);
			break;
		case FINGER_TYPE_RING:
			Ring->SetFromLeapFinger(finger);
			break;
		case FINGER_TYPE_PINKY:
			Pinky->SetFromLeapFinger(finger);
			break;
		default:
			break;
		}
	}
}
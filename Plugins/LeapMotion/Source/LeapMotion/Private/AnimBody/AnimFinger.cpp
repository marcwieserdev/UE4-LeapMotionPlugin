#include "LeapMotionPrivatePCH.h"
#include "LeapFinger.h"
#include "LeapBone.h"
#include "AnimFinger.h"
#include "LeapInterfaceUtility.h"

UAnimFinger::UAnimFinger(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Metacarpal = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Metacarpal"));
	Proximal = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Proximal"));
	Intermediate = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Intermediate"));
	Distal = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Distal"));
}

bool UAnimFinger::Enabled()
{
	return Alpha == 1.f;
}

void UAnimFinger::SetEnabled(bool enable)
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
	Metacarpal->SetEnabled(enable);
	Proximal->SetEnabled(enable);
	Intermediate->SetEnabled(enable);
	Distal->SetEnabled(enable);
}

void UAnimFinger::TranslateFinger(FVector shift)
{
	//Shift all bones
	Metacarpal->TranslateBone(shift);
	Proximal->TranslateBone(shift);
	Intermediate->TranslateBone(shift);
	Distal->TranslateBone(shift);
}

void UAnimFinger::ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors)
{
	//Change Basis for all bones
	Metacarpal->ChangeBasis(PreBase, PostBase, adjustVectors);
	Proximal->ChangeBasis(PreBase, PostBase, adjustVectors);
	Intermediate->ChangeBasis(PreBase, PostBase, adjustVectors);
	Distal->ChangeBasis(PreBase, PostBase, adjustVectors);
}

void UAnimFinger::SetFromLeapFinger(ULeapFinger* finger)
{
	//For now just set the finger orientations, inverse them
	Metacarpal->Orientation = (finger->Metacarpal->Direction * -1).Rotation();
	Proximal->Orientation = (finger->Proximal->Direction * -1).Rotation();
	Intermediate->Orientation = (finger->Intermediate->Direction * -1).Rotation();
	Distal->Orientation = (finger->Distal->Direction * -1).Rotation();
}
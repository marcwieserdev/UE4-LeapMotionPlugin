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

void UAnimFinger::SetFromLeapFinger(ULeapFinger* finger, LeapHandType handType)
{
	//Orientation, we need the hand type to reverse matrix basis for left hand bones
	Metacarpal->Orientation = finger->Metacarpal->GetOrientation(handType);
	Proximal->Orientation = finger->Proximal->GetOrientation(handType);
	Intermediate->Orientation = finger->Intermediate->GetOrientation(handType);
	Distal->Orientation = finger->Distal->GetOrientation(handType);

	//Position
	Metacarpal->Position = finger->Metacarpal->Center;
	Proximal->Position = finger->Proximal->Center;
	Intermediate->Position = finger->Intermediate->Center;
	Distal->Position = finger->Distal->Center;

	//Length
	Metacarpal->Length = finger->Metacarpal->Length;
	Proximal->Length = finger->Proximal->Length;
	Intermediate->Length = finger->Intermediate->Length;
	Distal->Length = finger->Distal->Length;
}
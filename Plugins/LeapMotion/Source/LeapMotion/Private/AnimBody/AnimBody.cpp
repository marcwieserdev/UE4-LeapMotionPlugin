#include "LeapMotionPrivatePCH.h"
#include "AnimBody.h"

UAnimBody::UAnimBody(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Left = PCIP.CreateDefaultSubobject<UAnimHand>(this, TEXT("Left"));
	Right = PCIP.CreateDefaultSubobject<UAnimHand>(this, TEXT("Right"));

	Head = PCIP.CreateDefaultSubobject<UAnimBone>(this, TEXT("Head"));
}


bool UAnimBody::Enabled()
{
	return Alpha == 1.f;
}

void UAnimBody::SetEnabled(bool enable)
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
	Left->SetEnabled(enable);
	Right->SetEnabled(enable);

	Head->SetEnabled(enable);
}

void UAnimBody::TranslateBody(FVector shift)
{
	//Shift all hands
	Left->TranslateHand(shift);
	Right->TranslateHand(shift);

	//Shift head
	Head->TranslateBone(shift);
}

void UAnimBody::ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors)
{
	//Change Basis for all hands
	Left->ChangeBasis(PreBase, PostBase, adjustVectors);
	Right->ChangeBasis(PreBase, PostBase, adjustVectors);

	//Careful with this tbh...
	Head->ChangeBasis(PreBase, PostBase, adjustVectors);
}
#include "LeapMotionPrivatePCH.h"
#include "LeapInterfaceUtility.h"
#include "AnimBone.h"

UAnimBone::UAnimBone(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	Scale = FVector(1, 1, 1);
}

bool UAnimBone::Enabled()
{
	return Alpha == 1.f;
}

void UAnimBone::SetEnabled(bool enable)
{
	enable ? Alpha = 1.f: Alpha = 0.f;
}

void UAnimBone::SetFromTransform(FTransform transform)
{
	Orientation = FRotator(transform.GetRotation());
	Position = transform.GetTranslation();
	Scale = transform.GetScale3D();
}

FTransform UAnimBone::GetTransform()
{
	return FTransform(FQuat(Orientation), Position, Scale);
}

void UAnimBone::TranslateBone(FVector shift)
{
	Position += shift;
}

void UAnimBone::ChangeBasis(FRotator PreBase, FRotator PostBase, bool adjustVectors)
{
	//Adjust the orientation
	FRotator postCombine = CombineRotators(Orientation, PostBase);
	Orientation = CombineRotators(PreBase, postCombine);

	//Rotate our vector/s
	if(adjustVectors)
		Position = PostBase.RotateVector(Position);
}
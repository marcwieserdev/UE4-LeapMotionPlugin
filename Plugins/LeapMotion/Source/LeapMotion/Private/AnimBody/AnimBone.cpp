#include "LeapMotionPrivatePCH.h"
#include "LeapInterfaceUtility.h"
#include "AnimBone.h"

UAnimBone::UAnimBone(const class FObjectInitializer& Init)
	: Super(Init)
{
	Scale = FVector(1, 1, 1);
}

bool UAnimBone::Enabled()
{
	return Alpha == 1.f;
}

void UAnimBone::SetEnabled(bool Enable)
{
	if (Enable)
	{
		Alpha = 1.f;
	}
	else
	{
		Alpha = 0.f;
	}
}

void UAnimBone::SetFromTransform(const FTransform& Transform)
{
	Orientation = FRotator(Transform.GetRotation());
	Position = Transform.GetTranslation();
	Scale = Transform.GetScale3D();
}

FTransform UAnimBone::GetTransform()
{
	return FTransform(FQuat(Orientation), Position, Scale);
}

void UAnimBone::TranslateBone(FVector Shift)
{
	Position += Shift;
}

void UAnimBone::TransformBone(FTransform& ByTransform)
{
	//The transform works differently we're only using it for timewarp right now, which is disabled (2.0.1)
	//FTransform Transform = GetTransform();
	//Transform.Accumulate(ByTransform);
	//SetFromTransform(Transform);

	Orientation = CombineRotators(Orientation, FRotator(ByTransform.GetRotation()));
	//Orientation = FRotator(Orientation.Quaternion() * ByTransform.GetRotation() );

	//Rotate the vector based on transform orientation
	Position = ByTransform.GetRotation().RotateVector(Position);
}

void UAnimBone::ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors)
{
	//Adjust the orientation
	FRotator PostCombine = CombineRotators(Orientation, PostBase);
	Orientation = CombineRotators(PreBase, PostCombine);

	//Rotate our vector/s
	if (AdjustVectors)
	{
		Position = PostBase.RotateVector(Position);
	}
}
#include "LeapMotionPrivatePCH.h"
#include "Bone.h"

UBone::UBone(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UBone::~UBone()
{
}

bool UBone::different(const UBone *other) const
{
	return (_bone != other->_bone);
}

bool UBone::equal(const UBone *other) const
{
	return (_bone == other->_bone);
}

BoneType type(Leap::Bone::Type type)
{
	switch(type)
	{
	case Leap::Bone::TYPE_METACARPAL:
		return (TYPE_METACARPAL);
	case Leap::Bone::TYPE_PROXIMAL:
		return (TYPE_PROXIMAL);
	case Leap::Bone::TYPE_INTERMEDIATE:
		return (TYPE_INTERMEDIATE);
	case Leap::Bone::TYPE_DISTAL:
		return (TYPE_DISTAL);
	default:
		return (TYPE_ERROR);
	}
}

void UBone::setBone(const Leap::Bone &bone)
{
	_bone = bone;

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _bone.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);

	Basis = (FMatrix(inX, inY, inZ, inW));
	Center = convertAndScaleLeapToUE(_bone.center());
	Direction = convertAndScaleLeapToUE(_bone.direction());
	IsValid = _bone.isValid();
	Length = _bone.length();
	NextJoint = convertAndScaleLeapToUE(_bone.nextJoint());
	PrevJoint = convertAndScaleLeapToUE(_bone.prevJoint());
	Type = type(_bone.type());
	Width = _bone.width();
}
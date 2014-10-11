#include "LeapMotionPrivatePCH.h"
#include "Bone.h"

UBone::UBone(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UBone::~UBone()
{
}

FMatrix UBone::basis() const
{
	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _bone.basis();
	inX.Set(matrix.xBasis.x,matrix.xBasis.y,matrix.xBasis.z);
	inY.Set(matrix.yBasis.x,matrix.yBasis.y,matrix.yBasis.z);
	inZ.Set(matrix.zBasis.x,matrix.zBasis.y,matrix.zBasis.z);
	inW.Set(matrix.origin.x,matrix.origin.y,matrix.origin.z);
	return (FMatrix(inX, inY, inZ, inW));
}

FVector UBone::Center() const
{
	Leap::Vector vect;

	vect = _bone.center();
	return (convertAndScaleLeapToUE(vect));
}

FVector UBone::Direction() const
{
	Leap::Vector vect;

	vect = _bone.direction();
	return (convertAndScaleLeapToUE(vect));
}

bool UBone::IsValid() const
{
	return (_bone.isValid());
}

float UBone::Length() const
{
	return (_bone.length());
}

FVector UBone::nextJoint() const
{
	Leap::Vector vect;

	vect = _bone.nextJoint();
	return (convertAndScaleLeapToUE(vect));
}

bool UBone::equal(const UBone *other) const
{
	return (_bone == other->_bone);
}

bool UBone::different(const UBone *other) const
{
	return (_bone != other->_bone);
}

FVector UBone::prevJoint() const
{
	Leap::Vector vect;

	vect = _bone.prevJoint();
	return (convertAndScaleLeapToUE(vect));
}

BoneType UBone::Type() const
{
	switch(_bone.type())
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

float UBone::Width() const
{
	return (_bone.width());
}

void UBone::setBone(const Leap::Bone &bone)
{
	_bone = bone;
}
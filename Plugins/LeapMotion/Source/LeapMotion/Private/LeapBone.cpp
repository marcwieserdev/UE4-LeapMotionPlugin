#include "LeapMotionPrivatePCH.h"
#include "LeapBone.h"

class PrivateBone
{
public:
	Leap::Bone bone;
};

ULeapBone::ULeapBone(const FObjectInitializer &init) : UObject(init), _private(new PrivateBone())
{
}

ULeapBone::~ULeapBone()
{
	delete _private;
}

void ULeapBone::CleanupRootReferences()
{
	this->RemoveFromRoot();
}

bool ULeapBone::different(const ULeapBone *other) const
{
	return (_private->bone != other->_private->bone);
}

bool ULeapBone::equal(const ULeapBone *other) const
{
	return (_private->bone == other->_private->bone);
}

LeapBoneType type(Leap::Bone::Type type)
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

void ULeapBone::setBone(const Leap::Bone &bone)
{
	_private->bone = bone;

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _private->bone.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);

	Basis = (FMatrix(inX, inY, inZ, inW));
	Center = convertAndScaleLeapToUE(_private->bone.center());
	Direction = convertLeapToUE(_private->bone.direction());
	IsValid = _private->bone.isValid();
	Length = _private->bone.length();
	NextJoint = convertAndScaleLeapToUE(_private->bone.nextJoint());
	PrevJoint = convertAndScaleLeapToUE(_private->bone.prevJoint());
	Type = type(_private->bone.type());
	Width = _private->bone.width();
}
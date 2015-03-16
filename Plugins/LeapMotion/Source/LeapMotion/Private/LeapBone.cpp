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


FRotator ULeapBone::GetOrientation(LeapHandType handType)
{
	if (handType == LeapHandType::HAND_LEFT)
		return swapLeftHandRuleForRight(Basis).Rotator();
	else
		return Basis.Rotator();
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

	Basis = convertLeapBasisMatrix(_private->bone.basis());
	Center = convertAndScaleLeapToUE(_private->bone.center());
	Direction = convertLeapToUE(_private->bone.direction());
	//Orientation = FRotationMatrix::MakeFromZX(PalmNormal*-1.f, Direction).Rotator();
	IsValid = _private->bone.isValid();
	Length = _private->bone.length();
	NextJoint = convertAndScaleLeapToUE(_private->bone.nextJoint());
	PrevJoint = convertAndScaleLeapToUE(_private->bone.prevJoint());
	Type = type(_private->bone.type());
	Width = _private->bone.width();
}
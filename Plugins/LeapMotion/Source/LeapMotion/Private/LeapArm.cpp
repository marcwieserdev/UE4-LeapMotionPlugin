#include "LeapMotionPrivatePCH.h"

class PrivateArm
{
public:
	Leap::Arm arm;
};

ULeapArm::ULeapArm(const FObjectInitializer &init) : UObject(init), _private(new PrivateArm())
{
}

ULeapArm::~ULeapArm()
{
	delete _private;
}

void ULeapArm::CleanupRootReferences()
{
	this->RemoveFromRoot();
}

FRotator ULeapArm::GetOrientation(LeapHandType handType)
{
	if (handType == LeapHandType::HAND_LEFT)
		return swapLeftHandRuleForRight(Basis).Rotator();
	else
		return Basis.Rotator();
}


bool ULeapArm::operator!=(const ULeapArm &arm) const
{
	return (arm._private->arm != this->_private->arm);
}

bool ULeapArm::operator==(const ULeapArm &arm) const
{
	return (arm._private->arm == this->_private->arm);
}

void ULeapArm::setArm(const Leap::Arm &arm)
{
	_private->arm = arm;

	Basis = convertLeapBasisMatrix(_private->arm.basis());
	Center = convertAndScaleLeapToUE(_private->arm.center());
	Direction = convertLeapToUE(_private->arm.direction());
	ElbowPosition = convertAndScaleLeapToUE(_private->arm.elbowPosition());
	IsValid = _private->arm.isValid();
	Width = _private->arm.width();
	WristPosition = convertAndScaleLeapToUE(_private->arm.wristPosition());
}
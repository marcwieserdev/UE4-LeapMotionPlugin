#include "LeapMotionPrivatePCH.h"

class PrivateArm
{
public:
	Leap::Arm Arm;
};

ULeapArm::ULeapArm(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateArm())
{
}

ULeapArm::~ULeapArm()
{
	delete Private;
}

void ULeapArm::CleanupRootReferences()
{
	this->RemoveFromRoot();
}

FRotator ULeapArm::GetOrientation(LeapHandType HandType)
{
	if (HandType == LeapHandType::HAND_LEFT)
	{
		return SwapLeftHandRuleForRight(Basis).Rotator();
	}
	else
	{
		return Basis.Rotator();
	}
}


bool ULeapArm::operator!=(const ULeapArm &Arm) const
{
	return (Arm.Private->Arm != this->Private->Arm);
}

bool ULeapArm::operator==(const ULeapArm &Arm) const
{
	return (Arm.Private->Arm == this->Private->Arm);
}

void ULeapArm::setArm(const Leap::Arm &Arm)
{
	Private->Arm = Arm;

	Basis = ConvertLeapBasisMatrix(Private->Arm.basis());
	Center = ConvertAndScaleLeapToUE(Private->Arm.center());
	Direction = ConvertLeapToUE(Private->Arm.direction());
	ElbowPosition = ConvertAndScaleLeapToUE(Private->Arm.elbowPosition());
	IsValid = Private->Arm.isValid();
	Width = Private->Arm.width();
	WristPosition = ConvertAndScaleLeapToUE(Private->Arm.wristPosition());
}
#include "LeapMotionPrivatePCH.h"

UArm::UArm(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UArm::~UArm()
{
}

bool UArm::operator!=(const UArm &arm) const
{
	return (arm._arm != this->_arm);
}

bool UArm::operator==(const UArm &arm) const
{
	return (arm._arm == this->_arm);
}

void UArm::setArm(const Leap::Arm &arm)
{
	_arm = arm;

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _arm.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	Basis = (FMatrix(inX, inY, inZ, inW));

	Center = convertAndScaleLeapToUE(_arm.center());
	Direction = convertAndScaleLeapToUE(_arm.direction());
	ElbowPosition = convertAndScaleLeapToUE(_arm.elbowPosition());
	IsValid = _arm.isValid();
	Width = _arm.width();
	WristPosition = convertAndScaleLeapToUE(_arm.wristPosition());
}
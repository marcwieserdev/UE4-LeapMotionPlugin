#include "LeapMotionPrivatePCH.h"

UArm::UArm(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UArm::~UArm()
{
}

FMatrix UArm::basis()
{
	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _arm.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	return (FMatrix(inX, inY, inZ, inW));
}

FVector UArm::Center()
{
	Leap::Vector vect;

	vect = _arm.center();
	return (convertAndScaleLeapToUE(vect));
}

FVector UArm::Direction()
{
	Leap::Vector vect;

	vect = _arm.direction();
	return (convertAndScaleLeapToUE(vect));
}

FVector UArm::elbowPosition()
{
	Leap::Vector vect;

	vect = _arm.elbowPosition();
	return (convertAndScaleLeapToUE(vect));
}

bool UArm::IsValid()
{
	return (_arm.isValid());
}

float UArm::Width()
{
	return _arm.width();
}

FVector UArm::wristPosition()
{
	Leap::Vector vect;

	vect = _arm.wristPosition();
	return (convertAndScaleLeapToUE(vect));
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
}
#include "LeapMotionPrivatePCH.h"

class PrivateArm
{
public:
	Leap::Arm arm;
};

UArm::UArm(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateArm())
{
}

UArm::~UArm()
{
	delete _private;
}

bool UArm::operator!=(const UArm &arm) const
{
	return (arm._private->arm != this->_private->arm);
}

bool UArm::operator==(const UArm &arm) const
{
	return (arm._private->arm == this->_private->arm);
}

void UArm::setArm(const Leap::Arm &arm)
{
	_private->arm = arm;

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _private->arm.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	Basis = (FMatrix(inX, inY, inZ, inW));

	Center = convertAndScaleLeapToUE(_private->arm.center());
	Direction = convertAndScaleLeapToUE(_private->arm.direction());
	ElbowPosition = convertAndScaleLeapToUE(_private->arm.elbowPosition());
	IsValid = _private->arm.isValid();
	Width = _private->arm.width();
	WristPosition = convertAndScaleLeapToUE(_private->arm.wristPosition());
}
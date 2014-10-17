#include "LeapMotionPrivatePCH.h"

UHand::UHand(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UHand::~UHand()
{
}

ULeapFrame *UHand::Frame()
{
	if (!_frame)
		_frame = NewObject<ULeapFrame>(this);
	_frame->setFrame(_hand.frame());
	return (_frame);
}

UFingerList* UHand::Fingers()
{
	if(!_fingers)
		_fingers = NewObject<UFingerList>(this);
	_fingers->setFingerList(_hand.fingers());
	return (_fingers);
}

float UHand::RotationAngle(ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.rotationAngle(rframe));
}

float UHand::RotationAngleWithAxis(class ULeapFrame *frame, const FVector &axis)
{
	Leap::Frame rframe;
	Leap::Vector vector;

	rframe = frame->getFrame();
	vector.x = axis.X;
	vector.y = axis.Y;
	vector.z = axis.Z;
	return (_hand.rotationAngle(rframe, vector));
}

FMatrix UHand::RotationMatrix(const ULeapFrame *frame)
{
	Leap::Matrix matrix;
	Leap::Frame rframe;
	FVector inX, inY, inZ, inW;

	rframe = frame->getFrame();
	matrix = _hand.rotationMatrix(rframe);
	inX.Set(matrix.xBasis.x,matrix.xBasis.y,matrix.xBasis.z);
	inY.Set(matrix.yBasis.x,matrix.yBasis.y,matrix.yBasis.z);
	inZ.Set(matrix.zBasis.x,matrix.zBasis.y,matrix.zBasis.z);
	inW.Set(matrix.origin.x,matrix.origin.y,matrix.origin.z);
	return (FMatrix(inX, inY, inZ, inW));
}


FVector UHand::RotationAxis(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _hand.rotationAxis(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float UHand::RotationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.rotationProbability(rframe));
}

float UHand::ScaleFactor(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.scaleFactor(rframe));
}

float UHand::ScaleProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.scaleProbability(rframe));
}

FVector UHand::Translation(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _hand.translation(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float UHand::TranslationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.translationProbability(rframe));
}

bool UHand::operator!=(const UHand &hand) const
{
	return (hand._hand != this->_hand);
}

bool UHand::operator==(const UHand &hand) const
{
	return (hand._hand == this->_hand);
}


void UHand::setHand(const Leap::Hand &hand)
{
	_hand = hand;

	//Set Properties
	if (!Arm)
		Arm = NewObject<UArm>(this, UArm::StaticClass());
	Arm->setArm(_hand.arm());

	PalmNormal = convertAndScaleLeapToUE(_hand.palmNormal());
	PalmPosition = convertAndScaleLeapToUE(_hand.palmPosition());
	PalmVelocity = convertAndScaleLeapToUE(_hand.palmVelocity());

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _hand.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	Basis = (FMatrix(inX, inY, inZ, inW));

	Confidence = _hand.confidence();
	Direction = convertAndScaleLeapToUE(_hand.direction());
	GrabStrength = _hand.grabStrength();
	IsLeft = _hand.isLeft();
	IsRight = _hand.isRight();
	PalmWidth = _hand.palmWidth();
	PinchStrength = _hand.pinchStrength();
	SphereCenter = convertAndScaleLeapToUE(_hand.sphereCenter());
	StabilizedPalmPosition = convertAndScaleLeapToUE(_hand.stabilizedPalmPosition());
	TimeVisible = _hand.timeVisible();

	Id = _hand.id();
}

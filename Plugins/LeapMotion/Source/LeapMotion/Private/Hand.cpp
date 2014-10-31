#include "LeapMotionPrivatePCH.h"

class PrivateHand
{
public:
	Leap::Hand hand;
	ULeapFrame* frame = NULL;
	UFingerList* fingers = NULL;
};

UHand::UHand(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateHand())
{
}

UHand::~UHand()
{
	delete _private;
}

ULeapFrame *UHand::Frame()
{
	if (_private->frame == NULL)
		_private->frame = NewObject<ULeapFrame>(this);
	_private->frame->setFrame(_private->hand.frame());
	return (_private->frame);
}

UFingerList* UHand::Fingers()
{
	if(_private->fingers == NULL)
		_private->fingers = NewObject<UFingerList>(this);
	_private->fingers->setFingerList(_private->hand.fingers());
	return (_private->fingers);
}

float UHand::RotationAngle(ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.rotationAngle(rframe));
}

float UHand::RotationAngleWithAxis(class ULeapFrame *frame, const FVector &axis)
{
	Leap::Frame rframe;
	Leap::Vector vector;

	rframe = frame->getFrame();
	vector.x = axis.X;
	vector.y = axis.Y;
	vector.z = axis.Z;
	return (_private->hand.rotationAngle(rframe, vector));
}

FMatrix UHand::RotationMatrix(const ULeapFrame *frame)
{
	Leap::Matrix matrix;
	Leap::Frame rframe;
	FVector inX, inY, inZ, inW;

	rframe = frame->getFrame();
	matrix = _private->hand.rotationMatrix(rframe);
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
	vect = _private->hand.rotationAxis(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float UHand::RotationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.rotationProbability(rframe));
}

float UHand::ScaleFactor(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.scaleFactor(rframe));
}

float UHand::ScaleProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.scaleProbability(rframe));
}

FVector UHand::Translation(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _private->hand.translation(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float UHand::TranslationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.translationProbability(rframe));
}

bool UHand::operator!=(const UHand &hand) const
{
	return (hand._private->hand != this->_private->hand);
}

bool UHand::operator==(const UHand &hand) const
{
	return (hand._private->hand == this->_private->hand);
}


void UHand::setHand(const Leap::Hand &hand)
{
	_private->hand = hand;

	//Set Properties
	if (!Arm)
		Arm = NewObject<UArm>(this, UArm::StaticClass());
	Arm->setArm(_private->hand.arm());

	PalmNormal = convertLeapToUE(_private->hand.palmNormal());
	PalmPosition = convertAndScaleLeapToUE(_private->hand.palmPosition());
	PalmVelocity = convertAndScaleLeapToUE(_private->hand.palmVelocity());

	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _private->hand.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	Basis = (FMatrix(inX, inY, inZ, inW));

	Confidence = _private->hand.confidence();
	Direction = convertLeapToUE(_private->hand.direction());
	GrabStrength = _private->hand.grabStrength();
	IsLeft = _private->hand.isLeft();
	IsRight = _private->hand.isRight();
	PalmWidth = _private->hand.palmWidth();
	PinchStrength = _private->hand.pinchStrength();
	SphereCenter = convertAndScaleLeapToUE(_private->hand.sphereCenter());
	StabilizedPalmPosition = convertAndScaleLeapToUE(_private->hand.stabilizedPalmPosition());
	TimeVisible = _private->hand.timeVisible();

	Id = _private->hand.id();
}

#include "LeapMotionPrivatePCH.h"

UHand::UHand(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UHand::~UHand()
{
}

bool UHand::isLeft() const
{
	return (_hand.isLeft());
}

bool UHand::isRight() const
{
	return (_hand.isRight());
}

bool UHand::IsValid() const
{
	return (_hand.isValid());
}

FVector UHand::palmNormal() const
{
	Leap::Vector vect;

	vect = _hand.palmNormal();
	return (FVector(-vect.z, vect.x, vect.y));
}

FVector UHand::palmPosition() const
{
	Leap::Vector vect;

	vect = _hand.palmPosition();
	return (FVector(-vect.z, vect.x, vect.y));
}

FVector UHand::palmVelocity() const
{
	Leap::Vector vect;

	vect = _hand.palmVelocity();
	return (FVector(-vect.z, vect.x, vect.y));
}

float UHand::confidence() const
{
	return (_hand.confidence());
}

FVector UHand::Direction() const
{
	Leap::Vector vect;

	vect = _hand.direction();
	return (FVector(-vect.z, vect.x, vect.y));
}

ULeapFrame *UHand::Frame()
{
	ULeapFrame *rframe;

	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_hand.frame());
	return (rframe);
}

float UHand::grabStrength() const
{
	return (_hand.grabStrength());
}

int32 UHand::Id() const
{
	return (_hand.id());
}

void UHand::setHand(const Leap::Hand &hand)
{
	_hand = hand;
}

float UHand::palmWidth() const
{
	return (_hand.palmWidth());
}

float UHand::pinchStrength() const
{
	return (_hand.pinchStrength());
}

float UHand::RotationAngle(ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.rotationAngle(rframe));
}

float UHand::rotationAngleWithAxis(class ULeapFrame *frame, const FVector &axis)
{
	Leap::Frame rframe;
	Leap::Vector vector;

	rframe = frame->getFrame();
	vector.x = axis.X;
	vector.y = axis.Y;
	vector.z = axis.Z;
	return (_hand.rotationAngle(rframe, vector));
}

FMatrix UHand::rotationMatrix(const ULeapFrame *frame)
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

FMatrix UHand::basis()
{
	Leap::Matrix matrix;
	FVector inX, inY, inZ, inW;

	matrix = _hand.basis();
	inX.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inY.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inZ.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	inW.Set(matrix.xBasis.x, matrix.xBasis.y, matrix.xBasis.z);
	return (FMatrix(inX, inY, inZ, inW));
}

FVector UHand::rotationAxis(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _hand.rotationAxis(rframe);
	return (FVector(-vect.z, vect.x, vect.y));
}

float UHand::rotationProbability(const ULeapFrame *frame)
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

float UHand::scaleProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_hand.scaleProbability(rframe));
}

FVector UHand::sphereCenter()
{
	Leap::Vector vect;

	vect = _hand.sphereCenter();
	return (FVector(-vect.z, vect.x, vect.y));
}

float UHand::SphereRadius() const
{
	return (_hand.sphereRadius());
}

FVector UHand::stabilizedPalmPosition()
{
	Leap::Vector vect;

	vect = _hand.stabilizedPalmPosition();
	return (FVector(-vect.z, vect.x, vect.y));
}

float UHand::timeVisible() const
{
	return (_hand.timeVisible());
}

FVector UHand::Translation(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _hand.translation(rframe);
	return (FVector(-vect.z, vect.x, vect.y));
}

float UHand::translationProbability(const ULeapFrame *frame) const
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

//Finger additions

UFingerList* UHand::fingers()
{
	UFingerList* fingers;
	fingers = ConstructObject<UFingerList>(UFingerList::StaticClass());
	fingers->setFingerList(_hand.fingers());
	return (fingers);
}
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
	return (FVector(vect.x, vect.y, vect.z));
}

FVector UHand::palmPosition() const
{
	Leap::Vector vect;

	vect = _hand.palmPosition();
	return (FVector(vect.x, vect.y, vect.z));
}

FVector UHand::palmVelocity() const
{
	Leap::Vector vect;

	vect = _hand.palmVelocity();
	return (FVector(vect.x, vect.y, vect.z));
}

float UHand::confidence() const
{
	return (_hand.confidence());
}

FVector UHand::Direction() const
{
	Leap::Vector vect;

	vect = _hand.direction();
	return (FVector(vect.x, vect.y, vect.z));
}

ULeapFrame *UHand::frame()
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
#include "LeapMotionPrivatePCH.h"
#include "Pointable.h"

UPointable::UPointable(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UPointable::~UPointable()
{
}

FVector UPointable::Direction() const
{
	Leap::Vector vect;

	vect = _pointable.direction();
	return (convertAndScaleLeapToUE(vect));
}

ULeapFrame *UPointable::Frame()
{
	ULeapFrame *rframe;

	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_pointable.frame());
	return (rframe);
}

UHand *UPointable::Hand()
{
	UHand *rhand;

	rhand = ConstructObject<UHand>(UHand::StaticClass());
	rhand->setHand(_pointable.hand());
	return (rhand);
}

int32 UPointable::Id() const
{
	return (_pointable.id());
}

bool UPointable::isExtended() const
{
	return (_pointable.isExtended());
}

bool UPointable::isFinger() const
{
	return (_pointable.isFinger());
}

bool UPointable::isTool() const
{
	return (_pointable.isTool());
}

bool UPointable::IsValid() const
{
	return (_pointable.isValid());
}

float UPointable::Length() const
{
	return (_pointable.length());
}

bool UPointable::equal(const UPointable *other) const
{
	return (_pointable == other->_pointable);
}

bool UPointable::different(const UPointable *other) const
{
	return (_pointable != other->_pointable);
}

FVector UPointable::stabilizedTipPosition()
{
	Leap::Vector vect;

	vect = _pointable.stabilizedTipPosition();
	return (convertAndScaleLeapToUE(vect));
}

float UPointable::timeVisible() const
{
	return (_pointable.timeVisible());
}

FVector UPointable::tipPosition() const
{
	Leap::Vector vect;

	vect = _pointable.tipPosition();
	return (convertAndScaleLeapToUE(vect));
}

FVector UPointable::tipVelocity() const
{
	Leap::Vector vect;

	vect = _pointable.tipVelocity();
	return (convertAndScaleLeapToUE(vect));
}

float UPointable::touchDistance() const
{
	return (_pointable.touchDistance());
}

LeapZone UPointable::touchZone() const
{
	switch (_pointable.touchZone())
	{
	case Leap::Pointable::Zone::ZONE_NONE:
		return (ZONE_NONE);
	case Leap::Pointable::Zone::ZONE_HOVERING:
		return (ZONE_HOVERING);
	case Leap::Pointable::Zone::ZONE_TOUCHING:
		return (ZONE_TOUCHING);
	default:
		return (ZONE_ERROR);
	}
}

float UPointable::Width() const
{
	return (_pointable.width());
}

void UPointable::setPointable(const Leap::Pointable &pointable)
{
	_pointable = pointable;
}

const Leap::Pointable &UPointable::getPointable() const
{
	return (_pointable);
}
#include "LeapMotionPrivatePCH.h"
#include "Pointable.h"

UPointable::UPointable(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UPointable::~UPointable()
{
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

bool UPointable::IsExtended()
{
	return (_pointable.isExtended());
}

bool UPointable::IsFinger()
{
	return (_pointable.isFinger());
}

bool UPointable::IsTool()
{
	return (_pointable.isTool());
}

bool UPointable::IsValid()
{
	return (_pointable.isValid());
}

bool UPointable::equal(const UPointable *other)
{
	return (_pointable == other->_pointable);
}

bool UPointable::different(const UPointable *other)
{
	return (_pointable != other->_pointable);
}

LeapZone touchZone(Leap::Pointable::Zone zone)
{
	switch (zone)
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

void UPointable::setPointable(const Leap::Pointable &pointable)
{
	_pointable = pointable;

	Direction = convertAndScaleLeapToUE(_pointable.direction());
	Id = _pointable.id();
	Length = _pointable.length();
	StabilizedTipPosition = convertAndScaleLeapToUE(_pointable.stabilizedTipPosition());
	TimeVisible = _pointable.timeVisible();
	TipPosition = convertAndScaleLeapToUE(_pointable.tipPosition());
	TipVelocity = convertAndScaleLeapToUE(_pointable.tipVelocity());
	TouchDistance = _pointable.touchDistance();
	TouchZone = touchZone(_pointable.touchZone());
	Width = _pointable.width();
}

const Leap::Pointable &UPointable::getPointable() const
{
	return (_pointable);
}
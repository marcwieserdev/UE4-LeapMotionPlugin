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
	if(!_rframe)
		_rframe = NewObject<ULeapFrame>(this);
	_rframe->setFrame(_pointable.frame());
	return (_rframe);
}

UHand *UPointable::Hand()
{
	if (!_rhand)
		_rhand = NewObject<UHand>(this, UHand::StaticClass());
	_rhand->setHand(_pointable.hand());
	return (_rhand);
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
	IsExtended = _pointable.isExtended();
	IsFinger = _pointable.isFinger();
	IsTool = _pointable.isTool();
	IsValid = _pointable.isValid();
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
#include "LeapMotionPrivatePCH.h"
#include "Pointable.h"

class PrivatePointable
{
public:
	Leap::Pointable pointable;
	ULeapFrame* frame = NULL;
	UHand* hand = NULL;
};

UPointable::UPointable(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivatePointable())
{
}

UPointable::~UPointable()
{
	delete _private;
}

ULeapFrame *UPointable::Frame()
{
	if(!_private->frame)
		_private->frame = NewObject<ULeapFrame>(this);
	_private->frame->setFrame(_private->pointable.frame());
	return (_private->frame);
}

UHand *UPointable::Hand()
{
	if (!_private->hand)
		_private->hand = NewObject<UHand>(this, UHand::StaticClass());
	_private->hand->setHand(_private->pointable.hand());
	return (_private->hand);
}

bool UPointable::equal(const UPointable *other)
{
	return (_private->pointable == other->_private->pointable);
}

bool UPointable::different(const UPointable *other)
{
	return (_private->pointable != other->_private->pointable);
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
	_private->pointable = pointable;

	Direction = convertAndScaleLeapToUE(_private->pointable.direction());
	Id = _private->pointable.id();
	IsExtended = _private->pointable.isExtended();
	IsFinger = _private->pointable.isFinger();
	IsTool = _private->pointable.isTool();
	IsValid = _private->pointable.isValid();
	Length = _private->pointable.length();
	StabilizedTipPosition = convertAndScaleLeapToUE(_private->pointable.stabilizedTipPosition());
	TimeVisible = _private->pointable.timeVisible();
	TipPosition = convertAndScaleLeapToUE(_private->pointable.tipPosition());
	TipVelocity = convertAndScaleLeapToUE(_private->pointable.tipVelocity());
	TouchDistance = _private->pointable.touchDistance();
	TouchZone = touchZone(_private->pointable.touchZone());
	Width = _private->pointable.width();
}

const Leap::Pointable &UPointable::getPointable() const
{
	return (_private->pointable);
}
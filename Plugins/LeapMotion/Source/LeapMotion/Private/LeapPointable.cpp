#include "LeapMotionPrivatePCH.h"
#include "LeapPointable.h"

class PrivatePointable
{
public:
	~PrivatePointable()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (frame)
			frame->CleanupRootReferences();
		if (hand)
			hand->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::Pointable pointable;
	ULeapFrame* frame = NULL;
	ULeapHand* hand = NULL;
};

ULeapPointable::ULeapPointable(const FObjectInitializer &init) : UObject(init), _private(new PrivatePointable())
{
}

ULeapPointable::~ULeapPointable()
{
	delete _private;
}
void ULeapPointable::CleanupRootReferences()
{
	_private->Cleanup();
    
    if (this->HasAnyFlags(RF_RootSet))
        this->RemoveFromRoot();
}

ULeapFrame *ULeapPointable::Frame()
{
	if (!_private->frame)
	{
		_private->frame = NewObject<ULeapFrame>(this);
		_private->frame->SetFlags(RF_RootSet);
	}
	_private->frame->setFrame(_private->pointable.frame());
	return (_private->frame);
}

ULeapHand *ULeapPointable::Hand()
{
	if (!_private->hand)
	{
		_private->hand = NewObject<ULeapHand>(this, ULeapHand::StaticClass());
		_private->hand->SetFlags(RF_RootSet);
	}
	_private->hand->setHand(_private->pointable.hand());
	return (_private->hand);
}

bool ULeapPointable::equal(const ULeapPointable *other)
{
	return (_private->pointable == other->_private->pointable);
}

bool ULeapPointable::different(const ULeapPointable *other)
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

void ULeapPointable::setPointable(const Leap::Pointable &pointable)
{
	_private->pointable = pointable;

	Direction = convertLeapToUE(_private->pointable.direction());
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

const Leap::Pointable &ULeapPointable::getPointable() const
{
	return (_private->pointable);
}
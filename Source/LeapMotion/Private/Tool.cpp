#include "LeapMotionPrivatePCH.h"

UTool::UTool(const FPostConstructInitializeProperties &init) : UPointable(init)
{
}

UTool::~UTool()
{
}

FVector UTool::Direction() const
{
	Leap::Vector vect;

	vect = _tool.direction();
	return (FVector(-vect.z, vect.x, vect.y));
}

ULeapFrame *UTool::frame()
{
	ULeapFrame *rframe;

	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_tool.frame());
	return (rframe);
}

UHand *UTool::Hand()
{
	UHand *rhand;

	rhand = ConstructObject<UHand>(UHand::StaticClass());
	rhand->setHand(_tool.hand());
	return (rhand);
}

int32 UTool::Id() const
{
	return (_tool.id());
}

bool UTool::isExtended() const
{
	return (_tool.isExtended());
}

bool UTool::isFinger() const
{
	return (_tool.isFinger());
}

bool UTool::isTool() const
{
	return (_tool.isTool());
}

bool UTool::IsValid() const
{
	return (_tool.isValid());
}

float UTool::Length() const
{
	return (_tool.length());
}

bool UTool::equal(const UPointable *other) const
{
	return (_tool == other->getPointable());
}

bool UTool::different(const UPointable *other) const
{
	return (_tool != other->getPointable());
}

FVector UTool::stabilizedTipPosition()
{
	Leap::Vector vect;

	vect = _tool.stabilizedTipPosition();
	return (FVector(-vect.z, vect.x, vect.y));
}

float UTool::timeVisible() const
{
	return (_tool.timeVisible());
}

FVector UTool::tipPosition() const
{
	Leap::Vector vect;

	vect = _tool.tipPosition();
	return (FVector(-vect.z, vect.x, vect.y));
}

FVector UTool::tipVelocity() const
{
	Leap::Vector vect;

	vect = _tool.tipVelocity();
	return (FVector(-vect.z, vect.x, vect.y));
}

float UTool::touchDistance() const
{
	return (_tool.touchDistance());
}

LeapZone UTool::touchZone() const
{
	switch (_tool.touchZone())
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

float UTool::Width() const
{
	return (_tool.width());
}

void UTool::setTool(const Leap::Tool &tool)
{
	_tool = tool;
}
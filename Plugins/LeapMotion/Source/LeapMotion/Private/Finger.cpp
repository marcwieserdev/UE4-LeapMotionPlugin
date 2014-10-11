#include "LeapMotionPrivatePCH.h"
#include "Finger.h"
#include "Bone.h"

UFinger::UFinger(const FPostConstructInitializeProperties &init) : UPointable(init)
{
}

UFinger::~UFinger()
{
}

UBone *UFinger::Bone(BoneType type)
{
	Leap::Bone::Type rtype;
	Leap::Bone rbone;
	UBone *bone;

	bone = ConstructObject<UBone>(UBone::StaticClass());
	switch(type)
	{
	case TYPE_METACARPAL:
		rtype = Leap::Bone::TYPE_METACARPAL;
		break;
	case TYPE_PROXIMAL:
		rtype = Leap::Bone::TYPE_PROXIMAL;
		break;
	case TYPE_INTERMEDIATE:
		rtype = Leap::Bone::TYPE_INTERMEDIATE;
		break;
	case TYPE_DISTAL:
		rtype = Leap::Bone::TYPE_DISTAL;
		break;
	default:
		rtype = Leap::Bone::TYPE_METACARPAL;
		break;
	}
	rbone = _finger.bone(rtype);
	bone->setBone(rbone);
	return (bone);
}

FVector UFinger::Direction() const
{
	Leap::Vector vect;

	vect = _finger.direction();
	return (convertAndScaleLeapToUE(vect));
}

ULeapFrame *UFinger::frame()
{
	ULeapFrame *rframe;

	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_finger.frame());
	return (rframe);
}

UHand *UFinger::Hand()
{
	UHand *rhand;

	rhand = ConstructObject<UHand>(UHand::StaticClass());
	rhand->setHand(_finger.hand());
	return (rhand);
}

int32 UFinger::Id() const
{
	return (_finger.id());
}

bool UFinger::isExtended() const
{
	return (_finger.isExtended());
}

bool UFinger::isFinger() const
{
	return (_finger.isFinger());
}

bool UFinger::isTool() const
{
	return (_finger.isTool());
}

bool UFinger::IsValid() const
{
	return (_finger.isValid());
}

float UFinger::Length() const
{
	return (_finger.length());
}

bool UFinger::equal(const UPointable *other) const
{
	return (_finger == other->getPointable());
}

bool UFinger::different(const UPointable *other) const
{
	return (_finger != other->getPointable());
}

FVector UFinger::stabilizedTipPosition()
{
	Leap::Vector vect;

	vect = _finger.stabilizedTipPosition();
	return (convertAndScaleLeapToUE(vect));
}

float UFinger::timeVisible() const
{
	return (_finger.timeVisible());
}

FVector UFinger::tipPosition() const
{
	Leap::Vector vect;

	vect = _finger.tipPosition();
	return (convertAndScaleLeapToUE(vect));
}

FVector UFinger::tipVelocity() const
{
	Leap::Vector vect;

	vect = _finger.tipVelocity();
	return (convertAndScaleLeapToUE(vect));
}

float UFinger::touchDistance() const
{
	return (_finger.touchDistance());
}

LeapZone UFinger::touchZone() const
{
	switch (_finger.touchZone())
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

float UFinger::Width() const
{
	return (_finger.width());
}

void UFinger::setFinger(const Leap::Finger &finger)
{
	_finger = finger;
}
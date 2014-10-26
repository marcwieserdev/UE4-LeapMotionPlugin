#include "LeapMotionPrivatePCH.h"
#include "Finger.h"
#include "Bone.h"


class PrivateFinger
{
public:
	Leap::Finger finger;
};


UFinger::UFinger(const FPostConstructInitializeProperties &init) : UPointable(init), _private(new PrivateFinger())
{
}

UFinger::~UFinger()
{
	delete _private;
}

UBone *UFinger::Bone(BoneType type)
{
	Leap::Bone::Type rtype;
	Leap::Bone rbone;
	UBone *bone;

	bone = NewObject<UBone>(this, UBone::StaticClass());
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
	rbone = _private->finger.bone(rtype);
	bone->setBone(rbone);
	return (bone);
}

void UFinger::setFinger(const Leap::Finger &finger)
{
	_private->finger = finger;

	setPointable(_private->finger);

	//Set convenience bones
	if (!Metacarpal)
		Metacarpal = NewObject<UBone>(this, UBone::StaticClass());
	Metacarpal->setBone(_private->finger.bone(Leap::Bone::TYPE_METACARPAL));

	if (!Proximal)
		Proximal = NewObject<UBone>(this, UBone::StaticClass());
	Proximal->setBone(_private->finger.bone(Leap::Bone::TYPE_PROXIMAL));

	if (!Intermediate)
		Intermediate = NewObject<UBone>(this, UBone::StaticClass());
	Intermediate->setBone(_private->finger.bone(Leap::Bone::TYPE_INTERMEDIATE));

	if (!Distal)
		Distal = NewObject<UBone>(this, UBone::StaticClass());
	Distal->setBone(_private->finger.bone(Leap::Bone::TYPE_DISTAL));
}
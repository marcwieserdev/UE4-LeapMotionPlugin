#include "LeapMotionPrivatePCH.h"
#include "LeapFinger.h"
#include "LeapBone.h"


class PrivateFinger
{
public:
	LeapFingerType ueFingerType(Leap::Finger::Type type){
		switch (type){
		case Leap::Finger::Type::TYPE_THUMB:
			return FINGER_TYPE_THUMB;
			break;
		case Leap::Finger::Type::TYPE_INDEX:
			return FINGER_TYPE_INDEX;
			break;
		case Leap::Finger::Type::TYPE_MIDDLE:
			return FINGER_TYPE_MIDDLE;
			break;
		case Leap::Finger::Type::TYPE_RING:
			return FINGER_TYPE_RING;
			break;
		case Leap::Finger::Type::TYPE_PINKY:
			return FINGER_TYPE_PINKY;
			break;
		default:
			UE_LOG(LeapPluginLog, Warning, TEXT("Warning! LeapFingerType, unknown type."));
			return FINGER_TYPE_THUMB;
			break;
		}
	}

	Leap::Finger finger;
};

ULeapFinger::ULeapFinger(const FObjectInitializer &init) : ULeapPointable(init), _private(new PrivateFinger())
{
}

ULeapFinger::~ULeapFinger()
{
	delete _private;
}

void ULeapFinger::CleanupRootReferences()
{
    ULeapPointable::CleanupRootReferences();
    
	if (this->HasAnyFlags(RF_RootSet))
		this->RemoveFromRoot();
}

ULeapBone *ULeapFinger::Bone(LeapBoneType type)
{
	Leap::Bone::Type rtype;
	Leap::Bone rbone;
	ULeapBone *bone;

	bone = NewObject<ULeapBone>(this, ULeapBone::StaticClass());
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


void ULeapFinger::setFinger(const Leap::Finger &finger)
{
	_private->finger = finger;

	setPointable(_private->finger);

	//Set convenience bones
	if (!Metacarpal)
		Metacarpal = NewObject<ULeapBone>(this, ULeapBone::StaticClass());
	Metacarpal->setBone(_private->finger.bone(Leap::Bone::TYPE_METACARPAL));

	if (!Proximal)
		Proximal = NewObject<ULeapBone>(this, ULeapBone::StaticClass());
	Proximal->setBone(_private->finger.bone(Leap::Bone::TYPE_PROXIMAL));

	if (!Intermediate)
		Intermediate = NewObject<ULeapBone>(this, ULeapBone::StaticClass());
	Intermediate->setBone(_private->finger.bone(Leap::Bone::TYPE_INTERMEDIATE));

	if (!Distal)
		Distal = NewObject<ULeapBone>(this, ULeapBone::StaticClass());
	Distal->setBone(_private->finger.bone(Leap::Bone::TYPE_DISTAL));

	//Set type
	Type = _private->ueFingerType(_private->finger.type());
}
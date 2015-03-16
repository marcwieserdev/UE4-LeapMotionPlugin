#include "LeapMotionPrivatePCH.h"

class PrivateHand
{
public:
	~PrivateHand()
	{
		if(!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (fingers)
			fingers->CleanupRootReferences();
		if (frame)
			frame->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::Hand hand;
	ULeapFrame* frame = NULL;
	ULeapFingerList* fingers = NULL;
};

ULeapHand::ULeapHand(const FObjectInitializer &init) : UObject(init), _private(new PrivateHand())
{
}

ULeapHand::~ULeapHand()
{
	delete _private;
}

void ULeapHand::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapFrame *ULeapHand::Frame()
{
	if (_private->frame == NULL)
	{
		_private->frame = NewObject<ULeapFrame>(this);
		_private->frame->SetFlags(RF_RootSet);
	}
	_private->frame->setFrame(_private->hand.frame());
	return (_private->frame);
}

ULeapFingerList* ULeapHand::Fingers()
{
	if (_private->fingers == NULL){
		_private->fingers = NewObject<ULeapFingerList>(this);
		//_private->fingers->SetFlags(RF_RootSet);
	}
	_private->fingers->setFingerList(_private->hand.fingers());
	return (_private->fingers);
}

float ULeapHand::RotationAngle(ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.rotationAngle(rframe));
}

float ULeapHand::RotationAngleWithAxis(class ULeapFrame *frame, const FVector &axis)
{
	Leap::Frame rframe;
	Leap::Vector vector;

	rframe = frame->getFrame();
	vector.x = axis.X;
	vector.y = axis.Y;
	vector.z = axis.Z;
	return (_private->hand.rotationAngle(rframe, vector));
}

FMatrix ULeapHand::RotationMatrix(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return convertLeapBasisMatrix(_private->hand.rotationMatrix(rframe));
}


FVector ULeapHand::RotationAxis(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _private->hand.rotationAxis(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float ULeapHand::RotationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.rotationProbability(rframe));
}

float ULeapHand::ScaleFactor(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.scaleFactor(rframe));
}

float ULeapHand::ScaleProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.scaleProbability(rframe));
}

FVector ULeapHand::Translation(const ULeapFrame *frame)
{
	Leap::Frame rframe;
	Leap::Vector vect;

	rframe = frame->getFrame();
	vect = _private->hand.translation(rframe);
	return (convertAndScaleLeapToUE(vect));
}

float ULeapHand::TranslationProbability(const ULeapFrame *frame)
{
	Leap::Frame rframe;

	rframe = frame->getFrame();
	return (_private->hand.translationProbability(rframe));
}

bool ULeapHand::operator!=(const ULeapHand &hand) const
{
	return (hand._private->hand != this->_private->hand);
}

bool ULeapHand::operator==(const ULeapHand &hand) const
{
	return (hand._private->hand == this->_private->hand);
}


void ULeapHand::setHand(const Leap::Hand &hand)
{
	_private->hand = hand;

	//Set Properties
	if (Arm == NULL || !Arm->IsValidLowLevel())
		Arm = NewObject<ULeapArm>(this, ULeapArm::StaticClass());
	Arm->setArm(_private->hand.arm());

	Confidence = _private->hand.confidence();
	Direction = convertLeapToUE(_private->hand.direction());
	GrabStrength = _private->hand.grabStrength();
	IsLeft = _private->hand.isLeft();
	IsRight = _private->hand.isRight();
	PalmWidth = _private->hand.palmWidth();
	PinchStrength = _private->hand.pinchStrength();
	SphereCenter = convertAndScaleLeapToUE(_private->hand.sphereCenter());
	StabilizedPalmPosition = convertAndScaleLeapToUE(_private->hand.stabilizedPalmPosition());
	TimeVisible = _private->hand.timeVisible();

	PalmNormal = convertLeapToUE(_private->hand.palmNormal());
	PalmPosition = convertAndScaleLeapToUE(_private->hand.palmPosition());
	PalmVelocity = convertAndScaleLeapToUE(_private->hand.palmVelocity());

	PalmOrientation = FRotationMatrix::MakeFromZX(PalmNormal*-1.f, Direction).Rotator();

	Basis = convertLeapBasisMatrix(_private->hand.basis());

	//Convenience Setting, allows for easy branching in blueprint
	if (IsLeft){
		HandType = LeapHandType::HAND_LEFT;
	}
	else if (IsRight){
		HandType = LeapHandType::HAND_RIGHT;
	}
	else{
		HandType = LeapHandType::HAND_UNKNOWN;
	}

	Id = _private->hand.id();
}

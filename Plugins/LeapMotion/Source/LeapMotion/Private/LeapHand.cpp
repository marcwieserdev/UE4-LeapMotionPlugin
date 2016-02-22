#include "LeapMotionPrivatePCH.h"

class PrivateHand
{
public:
	~PrivateHand()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		/*if (Fingers)
		{
			Fingers->CleanupRootReferences();
		}
		if (Frame)
		{
			Frame->CleanupRootReferences();
		}
		CleanupCalled = true;*/
	}
	bool CleanupCalled = false;
	Leap::Hand Hand;
	ULeapFrame* Frame = NULL;
	ULeapFingerList* Fingers = NULL;
};

ULeapHand::ULeapHand(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateHand())
{
}

ULeapHand::~ULeapHand()
{
	delete Private;
}

void ULeapHand::CleanupRootReferences()
{
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapFrame *ULeapHand::Frame()
{
	if (Private->Frame == NULL)
	{
		Private->Frame = NewObject<ULeapFrame>(this);
		Private->Frame->SetFlags(RF_ClassDefaultObject);
	}
	Private->Frame->SetFrame(Private->Hand.frame());
	return (Private->Frame);
}

ULeapFingerList* ULeapHand::Fingers()
{
	if (Private->Fingers == NULL)
	{
		Private->Fingers = NewObject<ULeapFingerList>(this);
		Private->Fingers->SetFlags(RF_ClassDefaultObject);
	}
	Private->Fingers->SetFingerList(Private->Hand.fingers());
	return (Private->Fingers);
}

float ULeapHand::RotationAngle(ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return (Private->Hand.rotationAngle(RFrame));
}

float ULeapHand::RotationAngleWithAxis(class ULeapFrame *Frame, const FVector &Axis)
{
	Leap::Frame RFrame;
	Leap::Vector Vector;

	RFrame = Frame->GetFrame();
	Vector.x = Axis.X;
	Vector.y = Axis.Y;
	Vector.z = Axis.Z;
	return (Private->Hand.rotationAngle(RFrame, Vector));
}

FMatrix ULeapHand::RotationMatrix(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return ConvertLeapBasisMatrix(Private->Hand.rotationMatrix(RFrame));
}


FVector ULeapHand::RotationAxis(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;
	Leap::Vector Vector;

	RFrame = Frame->GetFrame();
	Vector = Private->Hand.rotationAxis(RFrame);
	return (ConvertAndScaleLeapToUE(Vector));
}

float ULeapHand::RotationProbability(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return (Private->Hand.rotationProbability(RFrame));
}

float ULeapHand::ScaleFactor(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return (Private->Hand.scaleFactor(RFrame));
}

float ULeapHand::ScaleProbability(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return (Private->Hand.scaleProbability(RFrame));
}

FVector ULeapHand::Translation(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;
	Leap::Vector Vector;

	RFrame = Frame->GetFrame();
	Vector = Private->Hand.translation(RFrame);
	return (ConvertAndScaleLeapToUE(Vector));
}

float ULeapHand::TranslationProbability(const ULeapFrame *Frame)
{
	Leap::Frame RFrame;

	RFrame = Frame->GetFrame();
	return (Private->Hand.translationProbability(RFrame));
}

bool ULeapHand::operator!=(const ULeapHand &Hand) const
{
	return (Hand.Private->Hand != this->Private->Hand);
}

bool ULeapHand::operator==(const ULeapHand &Hand) const
{
	return (Hand.Private->Hand == this->Private->Hand);
}


void ULeapHand::SetHand(const Leap::Hand &Hand)
{
	Private->Hand = Hand;

	//Set Properties
	if (Arm == NULL || !Arm->IsValidLowLevel())
		Arm = NewObject<ULeapArm>(this, ULeapArm::StaticClass());
	Arm->setArm(Private->Hand.arm());

	Confidence = Private->Hand.confidence();
	Direction = ConvertLeapToUE(Private->Hand.direction());
	GrabStrength = Private->Hand.grabStrength();
	IsLeft = Private->Hand.isLeft();
	IsRight = Private->Hand.isRight();
	PalmWidth = ScaleLeapToUE(Private->Hand.palmWidth());
	PinchStrength = Private->Hand.pinchStrength();
	SphereCenter = ConvertAndScaleLeapToUE(Private->Hand.sphereCenter());
	SphereRadius = ScaleLeapToUE(Private->Hand.sphereRadius());
	StabilizedPalmPosition = ConvertAndScaleLeapToUE(Private->Hand.stabilizedPalmPosition());
	TimeVisible = Private->Hand.timeVisible();

	PalmNormal = ConvertLeapToUE(Private->Hand.palmNormal());
	PalmPosition = ConvertAndScaleLeapToUE(Private->Hand.palmPosition());
	PalmVelocity = ConvertAndScaleLeapToUE(Private->Hand.palmVelocity());

	PalmOrientation = FRotationMatrix::MakeFromZX(PalmNormal*-1.f, Direction).Rotator();

	Basis = ConvertLeapBasisMatrix(Private->Hand.basis());

	//Convenience Setting, allows for easy branching in blueprint
	if (IsLeft)
	{
		HandType = LeapHandType::HAND_LEFT;
	}
	else if (IsRight)
	{
		HandType = LeapHandType::HAND_RIGHT;
	}
	else
	{
		HandType = LeapHandType::HAND_UNKNOWN;
	}

	Id = Private->Hand.id();
}

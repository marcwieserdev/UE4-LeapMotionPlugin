#include "LeapMotionPrivatePCH.h"
#include "LeapPointable.h"

class PrivatePointable
{
public:
	~PrivatePointable()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		if (Frame)
		{
			Frame->CleanupRootReferences();
		}
		if (Hand)
		{
			Hand->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::Pointable Pointable;
	ULeapFrame* Frame = NULL;
	ULeapHand* Hand = NULL;
};

ULeapPointable::ULeapPointable(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivatePointable())
{
}

ULeapPointable::~ULeapPointable()
{
	delete Private;
}
void ULeapPointable::CleanupRootReferences()
{
	Private->Cleanup();
    
	if (this->HasAnyFlags(RF_RootSet))
	{
		this->RemoveFromRoot();
	}
}

ULeapFrame *ULeapPointable::Frame()
{
	if (!Private->Frame)
	{
		Private->Frame = NewObject<ULeapFrame>(this);
		Private->Frame->SetFlags(RF_RootSet);
	}
	Private->Frame->SetFrame(Private->Pointable.frame());
	return (Private->Frame);
}

ULeapHand *ULeapPointable::Hand()
{
	if (!Private->Hand)
	{
		Private->Hand = NewObject<ULeapHand>(this, ULeapHand::StaticClass());
		Private->Hand->SetFlags(RF_RootSet);
	}
	Private->Hand->SetHand(Private->Pointable.hand());
	return (Private->Hand);
}

bool ULeapPointable::Equal(const ULeapPointable *Other)
{
	return (Private->Pointable == Other->Private->Pointable);
}

bool ULeapPointable::Different(const ULeapPointable *Other)
{
	return (Private->Pointable != Other->Private->Pointable);
}

LeapZone ConvertTouchZone(Leap::Pointable::Zone Zone)
{
	switch (Zone)
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

void ULeapPointable::SetPointable(const Leap::Pointable &Pointable)
{
	Private->Pointable = Pointable;

	Direction = ConvertLeapToUE(Private->Pointable.direction());
	Id = Private->Pointable.id();
	IsExtended = Private->Pointable.isExtended();
	IsFinger = Private->Pointable.isFinger();
	IsTool = Private->Pointable.isTool();
	IsValid = Private->Pointable.isValid();
	Length = ScaleLeapToUE(Private->Pointable.length());
	StabilizedTipPosition = ConvertAndScaleLeapToUE(Private->Pointable.stabilizedTipPosition());
	TimeVisible = Private->Pointable.timeVisible();
	TipPosition = ConvertAndScaleLeapToUE(Private->Pointable.tipPosition());
	TipVelocity = ConvertAndScaleLeapToUE(Private->Pointable.tipVelocity());
	TouchDistance = Private->Pointable.touchDistance();
	TouchZone = ConvertTouchZone(Private->Pointable.touchZone());
	Width = ScaleLeapToUE(Private->Pointable.width());
}

const Leap::Pointable &ULeapPointable::GetPointable() const
{
	return (Private->Pointable);
}
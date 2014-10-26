#include "LeapMotionPrivatePCH.h"

class PrivateInteractionBox
{
public:
	Leap::InteractionBox interactionBox;
};


UInteractionBox::UInteractionBox(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateInteractionBox())
{
}

UInteractionBox::~UInteractionBox()
{
	delete _private;
}

FVector UInteractionBox::DenormalizePoint(FVector vector) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_private->interactionBox.denormalizePoint(leapVect)));
}

FVector UInteractionBox::NormalizePoint(FVector vector, bool clamp) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_private->interactionBox.normalizePoint(leapVect, clamp)));
}

void UInteractionBox::setInteractionBox(const Leap::InteractionBox &InteractionBox)
{
	_private->interactionBox = InteractionBox;
	Center = convertAndScaleLeapToUE(_private->interactionBox.center());
	Depth = _private->interactionBox.depth();
	Height = _private->interactionBox.height();
	IsValid = _private->interactionBox.isValid();
	Width = _private->interactionBox.width();
}
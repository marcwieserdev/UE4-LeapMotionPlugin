#include "LeapMotionPrivatePCH.h"

UInteractionBox::UInteractionBox(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UInteractionBox::~UInteractionBox()
{
}

FVector UInteractionBox::DenormalizePoint(FVector vector) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_interactionBox.denormalizePoint(leapVect)));
}

FVector UInteractionBox::NormalizePoint(FVector vector, bool clamp) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_interactionBox.normalizePoint(leapVect, clamp)));
}

void UInteractionBox::setInteractionBox(const Leap::InteractionBox &InteractionBox)
{
	_interactionBox = InteractionBox;
	Center = convertAndScaleLeapToUE(_interactionBox.center());
	Depth = _interactionBox.depth();
	Height = _interactionBox.height();
	IsValid = _interactionBox.isValid();
	Width = _interactionBox.width();
}
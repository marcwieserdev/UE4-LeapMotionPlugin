#include "LeapMotionPrivatePCH.h"

UInteractionBox::UInteractionBox(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UInteractionBox::~UInteractionBox()
{
}

FVector UInteractionBox::Center() const
{
	return convertAndScaleLeapToUE(_interactionBox.center());
}

FVector UInteractionBox::DenormalizePoint(FVector vector) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_interactionBox.denormalizePoint(leapVect)));
}

float UInteractionBox::Depth() const 
{
	return _interactionBox.depth();
}

float UInteractionBox::Height() const 
{
	return _interactionBox.height();
}

bool UInteractionBox::IsValid() const 
{
	return _interactionBox.isValid();
}

FVector UInteractionBox::NormalizePoint(FVector vector, bool clamp) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_interactionBox.normalizePoint(leapVect, clamp)));
}

float UInteractionBox::Width() const
{
	return _interactionBox.width();
}

void UInteractionBox::setInteractionBox(const Leap::InteractionBox &InteractionBox)
{
	_interactionBox = InteractionBox;
}
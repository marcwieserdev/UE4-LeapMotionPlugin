#include "LeapMotionPrivatePCH.h"

class PrivateInteractionBox
{
public:
	Leap::InteractionBox interactionBox;
};


ULeapInteractionBox::ULeapInteractionBox(const FObjectInitializer &init) : UObject(init), _private(new PrivateInteractionBox())
{
}

ULeapInteractionBox::~ULeapInteractionBox()
{
	delete _private;
}

void ULeapInteractionBox::CleanupRootReferences()
{
	this->RemoveFromRoot();
}


FVector ULeapInteractionBox::DenormalizePoint(FVector vector) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_private->interactionBox.denormalizePoint(leapVect)));
}

FVector ULeapInteractionBox::NormalizePoint(FVector vector, bool clamp) const
{
	Leap::Vector leapVect = convertAndScaleUEToLeap(vector);
	return (convertAndScaleLeapToUE(_private->interactionBox.normalizePoint(leapVect, clamp)));
}

void ULeapInteractionBox::setInteractionBox(const Leap::InteractionBox &InteractionBox)
{
	_private->interactionBox = InteractionBox;
	Center = convertAndScaleLeapToUE(_private->interactionBox.center());
	Depth = _private->interactionBox.depth();
	Height = _private->interactionBox.height();
	IsValid = _private->interactionBox.isValid();
	Width = _private->interactionBox.width();
}
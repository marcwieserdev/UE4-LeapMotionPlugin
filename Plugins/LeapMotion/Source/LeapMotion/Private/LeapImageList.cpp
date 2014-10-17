#include "LeapMotionPrivatePCH.h"

ULeapImageList::ULeapImageList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapImageList::~ULeapImageList()
{
}

bool ULeapImageList::isEmpty() const
{
	return (_leapImages.isEmpty());
}

ULeapImage* ULeapImageList::getIndex(int32 index)
{
	ULeapImage* image;

	image = ConstructObject<ULeapImage>(ULeapImage::StaticClass());
	image->setLeapImage(_leapImages[index]);
	return (image);
}

ULeapImage* ULeapImageList::operator[](int index)
{
	return getIndex(index);
}

void ULeapImageList::setLeapImageList(const Leap::ImageList &LeapImageList)
{
	_leapImages = LeapImageList;

	Count = _leapImages.count();
}
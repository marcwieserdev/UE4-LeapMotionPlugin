#include "LeapMotionPrivatePCH.h"

ULeapImageList::ULeapImageList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

ULeapImageList::~ULeapImageList()
{
}

ULeapImage* ULeapImageList::getIndex(int32 index)
{
	//We need to use two separate objects to ensure we have two separate images
	if (index == 0)
	{
		if (_indexImage1 == NULL)
			_indexImage1 = NewObject<ULeapImage>(this);
		_indexImage1->setLeapImage(_leapImages[index]);
		return (_indexImage1);
	}
	else
	{
		if (_indexImage2 == NULL)
			_indexImage2 = NewObject<ULeapImage>(this);
		_indexImage2->setLeapImage(_leapImages[index]);
		return (_indexImage2);
	}
}

ULeapImage* ULeapImageList::operator[](int index)
{
	return getIndex(index);
}

void ULeapImageList::setLeapImageList(const Leap::ImageList &LeapImageList)
{
	_leapImages = LeapImageList;

	Count = _leapImages.count();
	IsEmpty = _leapImages.isEmpty();
}
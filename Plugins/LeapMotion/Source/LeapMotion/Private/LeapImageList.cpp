#include "LeapMotionPrivatePCH.h"

class PrivateLeapImageList
{
public:
	Leap::ImageList leapImages;
	ULeapImage* indexImage1 = NULL;
	ULeapImage* indexImage2 = NULL;
};

ULeapImageList::ULeapImageList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateLeapImageList())
{
}

ULeapImageList::~ULeapImageList()
{
	delete _private;
}

ULeapImage* ULeapImageList::getIndex(int32 index)
{
	//We need to use two separate objects to ensure we have two separate images
	if (index == 0)
	{
		if (_private->indexImage1 == NULL)
			_private->indexImage1 = NewObject<ULeapImage>(this);
		_private->indexImage1->setLeapImage(_private->leapImages[index]);
		return (_private->indexImage1);
	}
	else
	{
		if (_private->indexImage2 == NULL)
			_private->indexImage2 = NewObject<ULeapImage>(this);
		_private->indexImage2->setLeapImage(_private->leapImages[index]);
		return (_private->indexImage2);
	}
}

ULeapImage* ULeapImageList::operator[](int index)
{
	return getIndex(index);
}

void ULeapImageList::setLeapImageList(const Leap::ImageList &LeapImageList)
{
	_private->leapImages = LeapImageList;

	Count = _private->leapImages.count();
	IsEmpty = _private->leapImages.isEmpty();
}
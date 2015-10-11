#include "LeapMotionPrivatePCH.h"

class PrivateLeapImageList
{
public:
	~PrivateLeapImageList()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (indexImage1)
			indexImage1->CleanupRootReferences();
		if (indexImage2)
			indexImage2->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::ImageList leapImages;
	ULeapImage* indexImage1 = NULL;
	ULeapImage* indexImage2 = NULL;
};

ULeapImageList::ULeapImageList(const FObjectInitializer &init) : UObject(init), _private(new PrivateLeapImageList())
{
}

ULeapImageList::~ULeapImageList()
{
	delete _private;
}

void ULeapImageList::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapImage* ULeapImageList::getIndex(int32 index)
{
	//We need to use two separate objects to ensure we have two separate images
	if (index == 0)
	{
		if (_private->indexImage1 == NULL)
		{
			_private->indexImage1 = NewObject<ULeapImage>(this);
			_private->indexImage1->SetFlags(RF_RootSet);
		}
		_private->indexImage1->setLeapImage(_private->leapImages[index]);
		return (_private->indexImage1);
	}
	else
	{
		if (_private->indexImage2 == NULL)
		{
			_private->indexImage2 = NewObject<ULeapImage>(this);
			_private->indexImage2->SetFlags(RF_RootSet);
		}
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
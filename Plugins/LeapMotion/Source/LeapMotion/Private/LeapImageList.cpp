#include "LeapMotionPrivatePCH.h"

class PrivateLeapImageList
{
public:
	~PrivateLeapImageList()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		/*if (IndexImage1)
		{
			IndexImage1->CleanupRootReferences();
		}
		if (IndexImage2)
		{
			IndexImage2->CleanupRootReferences();
		}*/
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::ImageList LeapImages;
	ULeapImage* IndexImage1 = NULL;
	ULeapImage* IndexImage2 = NULL;
};

ULeapImageList::ULeapImageList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateLeapImageList())
{
}

ULeapImageList::~ULeapImageList()
{
	delete Private;
}

void ULeapImageList::CleanupRootReferences()
{
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapImage* ULeapImageList::GetIndex(int32 Index)
{
	//We need to use two separate objects to ensure we have two separate images
	if (Index == 0)
	{
		if (Private->IndexImage1 == NULL)
		{
			Private->IndexImage1 = NewObject<ULeapImage>(this);
			Private->IndexImage1->SetFlags(RF_ClassDefaultObject);
		}
		Private->IndexImage1->SetLeapImage(Private->LeapImages[Index]);
		return (Private->IndexImage1);
	}
	else
	{
		if (Private->IndexImage2 == NULL)
		{
			Private->IndexImage2 = NewObject<ULeapImage>(this);
			Private->IndexImage2->SetFlags(RF_ClassDefaultObject);
		}
		Private->IndexImage2->SetLeapImage(Private->LeapImages[Index]);
		return (Private->IndexImage2);
	}
}

ULeapImage* ULeapImageList::operator[](int Index)
{
	return GetIndex(Index);
}

void ULeapImageList::SetLeapImageList(const Leap::ImageList &LeapImageList)
{
	Private->LeapImages = LeapImageList;

	Count = Private->LeapImages.count();
	IsEmpty = Private->LeapImages.isEmpty();
}
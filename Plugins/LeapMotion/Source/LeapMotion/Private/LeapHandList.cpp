#include "LeapMotionPrivatePCH.h"

class PrivateHandList
{
public:
	~PrivateHandList()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		if (Frontmost)
		{
			Frontmost->CleanupRootReferences();
		}
		if (Leftmost)
		{
			Leftmost->CleanupRootReferences();
		}
		if (Rightmost)
		{
			Rightmost->CleanupRootReferences();
		}
		if (IndexHand)
		{
			IndexHand->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::HandList Hands;
	ULeapHand* Frontmost = NULL;
	ULeapHand* Leftmost = NULL;
	ULeapHand* Rightmost = NULL;
	ULeapHand* IndexHand = NULL;
};

ULeapHandList::ULeapHandList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateHandList())
{
}

ULeapHandList::~ULeapHandList()
{
	delete Private;
}

void ULeapHandList::CleanupRootReferences()
{
	Private->Cleanup();
	this->RemoveFromRoot();
}

ULeapHand* ULeapHandList::Frontmost()
{
	if (Private->Frontmost == NULL)
	{
		Private->Frontmost = NewObject<ULeapHand>(this);
		Private->Frontmost->SetFlags(RF_RootSet);
	}
	Private->Frontmost->SetHand(Private->Hands.frontmost());
	return (Private->Frontmost);
}

ULeapHand* ULeapHandList::Leftmost()
{
	if (Private->Leftmost == NULL)
	{
		Private->Leftmost = NewObject<ULeapHand>(this);
		Private->Leftmost->SetFlags(RF_RootSet);
	}
	Private->Leftmost->SetHand(Private->Hands.leftmost());
	return (Private->Leftmost);
}

ULeapHand* ULeapHandList::Rightmost()
{
	if (Private->Rightmost == NULL)
	{
		Private->Rightmost = NewObject<ULeapHand>(this);
		Private->Rightmost->SetFlags(RF_RootSet);
	}
	Private->Rightmost->SetHand(Private->Hands.rightmost());
	return (Private->Rightmost);
}

ULeapHand* ULeapHandList::getIndex(int32 index)
{
	if (Private->IndexHand == NULL)
	{
		Private->IndexHand = NewObject<ULeapHand>(this);
		Private->IndexHand->SetFlags(RF_RootSet);
	}
	Private->IndexHand->SetHand(Private->Hands[index]);
	return (Private->IndexHand);
}

void ULeapHandList::SetHandList(const Leap::HandList &Handlist)
{
	Private->Hands = Handlist;

	Count = Private->Hands.count();
	IsEmpty = Private->Hands.isEmpty();
}
#include "LeapMotionPrivatePCH.h"

class PrivateHandList
{
public:
	~PrivateHandList()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (frontmost)
			frontmost->CleanupRootReferences();
		if (leftmost)
			leftmost->CleanupRootReferences();
		if (rightmost)
			rightmost->CleanupRootReferences();
		if (indexHand)
			indexHand->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::HandList hands;
	ULeapHand* frontmost = NULL;
	ULeapHand* leftmost = NULL;
	ULeapHand* rightmost = NULL;
	ULeapHand* indexHand = NULL;
};

ULeapHandList::ULeapHandList(const FObjectInitializer &init) : UObject(init), _private(new PrivateHandList())
{
}

ULeapHandList::~ULeapHandList()
{
	delete _private;
}

void ULeapHandList::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapHand* ULeapHandList::Frontmost()
{
	if (_private->frontmost == NULL)
	{
		_private->frontmost = NewObject<ULeapHand>(this);
		_private->frontmost->SetFlags(RF_RootSet);
	}
	_private->frontmost->setHand(_private->hands.frontmost());
	return (_private->frontmost);
}

ULeapHand* ULeapHandList::Leftmost()
{
	if (_private->leftmost == NULL)
	{
		_private->leftmost = NewObject<ULeapHand>(this);
		_private->leftmost->SetFlags(RF_RootSet);
	}
	_private->leftmost->setHand(_private->hands.leftmost());
	return (_private->leftmost);
}

ULeapHand* ULeapHandList::Rightmost()
{
	if (_private->rightmost == NULL)
	{
		_private->rightmost = NewObject<ULeapHand>(this);
		_private->rightmost->SetFlags(RF_RootSet);
	}
	_private->rightmost->setHand(_private->hands.rightmost());
	return (_private->rightmost);
}

ULeapHand* ULeapHandList::getIndex(int32 index)
{
	if (_private->indexHand == NULL)
	{
		_private->indexHand = NewObject<ULeapHand>(this);
		_private->indexHand->SetFlags(RF_RootSet);
	}
	_private->indexHand->setHand(_private->hands[index]);
	return (_private->indexHand);
}

void ULeapHandList::setHandList(const Leap::HandList &handlist)
{
	_private->hands = handlist;

	Count = _private->hands.count();
	IsEmpty = _private->hands.isEmpty();
}
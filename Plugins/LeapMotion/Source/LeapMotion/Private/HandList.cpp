#include "LeapMotionPrivatePCH.h"

class PrivateHandList
{
public:
	Leap::HandList hands;
	UHand* frontmost = NULL;
	UHand* leftmost = NULL;
	UHand* rightmost = NULL;
	UHand* indexHand = NULL;
};

UHandList::UHandList(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateHandList())
{
}

UHandList::~UHandList()
{
	delete _private;
}

UHand* UHandList::Frontmost()
{
	if (_private->frontmost == NULL)
		_private->frontmost = NewObject<UHand>(this);
	_private->frontmost->setHand(_private->hands.frontmost());
	return (_private->frontmost);
}

UHand* UHandList::Leftmost()
{
	if (_private->leftmost == NULL)
		_private->leftmost = NewObject<UHand>(this);
	_private->leftmost->setHand(_private->hands.leftmost());
	return (_private->leftmost);
}

UHand* UHandList::Rightmost()
{
	if (_private->rightmost == NULL)
		_private->rightmost = NewObject<UHand>(this);
	_private->rightmost->setHand(_private->hands.rightmost());
	return (_private->rightmost);
}

UHand* UHandList::getIndex(int32 index)
{
	if (_private->indexHand == NULL)
		_private->indexHand = NewObject<UHand>(this);
	_private->indexHand->setHand(_private->hands[index]);
	return (_private->indexHand);
}

void UHandList::setHandList(const Leap::HandList &handlist)
{
	_private->hands = handlist;

	Count = _private->hands.count();
	IsEmpty = _private->hands.isEmpty();
}
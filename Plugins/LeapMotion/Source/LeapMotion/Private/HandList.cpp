#include "LeapMotionPrivatePCH.h"

UHandList::UHandList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UHandList::~UHandList()
{
}

UHand* UHandList::Frontmost()
{
	if (!_frontmost)
		_frontmost = NewObject<UHand>(this);
	_frontmost->setHand(_hands.frontmost());
	return (_frontmost);
}

UHand* UHandList::Leftmost()
{
	if (!_leftmost)
		_leftmost = NewObject<UHand>(this);
	_leftmost->setHand(_hands.leftmost());
	return (_leftmost);
}

UHand* UHandList::Rightmost()
{
	if (!_rightmost)
		_rightmost = NewObject<UHand>(this);
	_rightmost->setHand(_hands.rightmost());
	return (_rightmost);
}

UHand* UHandList::getIndex(int32 index)
{
	if (!_indexHand)
		_indexHand = NewObject<UHand>(this);
	_indexHand->setHand(_hands[index]);
	return (_indexHand);
}

void UHandList::setHandList(const Leap::HandList &handlist)
{
	_hands = handlist;

	Count = _hands.count();
	IsEmpty = _hands.isEmpty();
}
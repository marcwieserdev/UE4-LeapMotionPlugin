#include "LeapMotionPrivatePCH.h"

UHandList::UHandList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UHandList::~UHandList()
{
}

UHand *UHandList::Frontmost()
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands.frontmost());
	return (hand);
}

UHand *UHandList::Leftmost()
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands.leftmost());
	return (hand);
}

UHand *UHandList::Rightmost()
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands.rightmost());
	return (hand);
}

UHand *UHandList::getIndex(int32 index)
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands[index]);
	return (hand);
}

void UHandList::setHandList(const Leap::HandList &handlist)
{
	_hands = handlist;

	Count = _hands.count();
	IsEmpty = _hands.isEmpty();
}
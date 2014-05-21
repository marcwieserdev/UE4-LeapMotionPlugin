#include "LeapMotionPrivatePCH.h"

UHandList::UHandList(const FPostConstructInitializeProperties &init) : UObject(init)
{
}

UHandList::~UHandList()
{
}

bool UHandList::isEmpty() const
{
	return (_hands.isEmpty());
}

int32 UHandList::Count()
{
	return (_hands.count());
}

UHand *UHandList::frontmost()
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands.frontmost());
	return (hand);
}

UHand *UHandList::leftmost()
{
	UHand *hand;

	hand = ConstructObject<UHand>(UHand::StaticClass());
	hand->setHand(_hands.leftmost());
	return (hand);
}

UHand *UHandList::rightmost()
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
}
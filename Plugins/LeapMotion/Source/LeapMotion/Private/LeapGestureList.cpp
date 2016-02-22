#include "LeapMotionPrivatePCH.h"

class PrivateGestureList
{
public:

	Leap::GestureList Gestures;
};

ULeapGestureList::ULeapGestureList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateGestureList())
{
}

ULeapGestureList::~ULeapGestureList()
{
	delete Private;
}

ULeapGesture* ULeapGestureList::GetIndex(int32 Index)
{
	if (PGesture == nullptr)
	{
		PGesture = NewObject<ULeapGesture>(this, ULeapGesture::StaticClass());
	}
	PGesture->SetGesture(Private->Gestures[Index]);
	return (PGesture);
}

ULeapGesture* ULeapGestureList::operator[](int Index)
{
	return GetIndex(Index);
}

void ULeapGestureList::SetGestureList(const Leap::GestureList &GestureList)
{
	Private->Gestures = GestureList;

	Count = Private->Gestures.count();
	IsEmpty = Private->Gestures.isEmpty();
}
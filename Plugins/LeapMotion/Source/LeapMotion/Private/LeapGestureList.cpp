#include "LeapMotionPrivatePCH.h"

class PrivateGestureList
{
public:
	~PrivateGestureList()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		/*if (Gesture)
		{
			Gesture->CleanupRootReferences();
		}*/
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::GestureList Gestures;
	ULeapGesture* Gesture = NULL;
};

ULeapGestureList::ULeapGestureList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateGestureList())
{
}

ULeapGestureList::~ULeapGestureList()
{
	delete Private;
}

void ULeapGestureList::CleanupRootReferences()
{
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapGesture* ULeapGestureList::GetIndex(int32 Index)
{
	if (Private->Gesture == NULL)
	{
		Private->Gesture = NewObject<ULeapGesture>(this, ULeapGesture::StaticClass());
		Private->Gesture->SetFlags(RF_ClassDefaultObject);
	}
	Private->Gesture->SetGesture(Private->Gestures[Index]);
	return (Private->Gesture);
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
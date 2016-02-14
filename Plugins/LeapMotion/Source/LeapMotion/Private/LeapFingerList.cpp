#include "LeapMotionPrivatePCH.h"
#include "LeapFingerList.h"
#include "LeapFinger.h"

class PrivateFingerList{
public:
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
		if (PointableById)
		{
			PointableById->CleanupRootReferences();
		}
		if (AppendedList)
		{
			AppendedList->CleanupRootReferences();
		}
		if (ExtendedList)
		{
			ExtendedList->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	~PrivateFingerList()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}

	bool CleanupCalled = false;
	Leap::FingerList Fingers;
	ULeapFinger* Frontmost = NULL;
	ULeapFinger* Leftmost = NULL;
	ULeapFinger* Rightmost = NULL;
	ULeapFinger* PointableById = NULL;
	ULeapFingerList* AppendedList = NULL;
	ULeapFingerList* ExtendedList = NULL;
};

ULeapFingerList::ULeapFingerList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateFingerList())
{
}

ULeapFingerList::~ULeapFingerList()
{
	delete Private;
}

void ULeapFingerList::CleanupRootReferences()
{
	Private->Cleanup();
	if (this->HasAnyFlags(RF_RootSet))
	{
		this->RemoveFromRoot();
	}
}

ULeapFingerList *ULeapFingerList::Append(const ULeapFingerList *List)
{
	if (Private->AppendedList == NULL)
	{
		Private->AppendedList = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
		Private->AppendedList->SetFlags(RF_RootSet);
	}
	Private->AppendedList->SetFingerList(Private->Fingers.append(List->Private->Fingers));
	return (Private->AppendedList);
}

ULeapFingerList *ULeapFingerList::Extended()
{
	if (Private->ExtendedList == NULL)
	{
		Private->ExtendedList = NewObject<ULeapFingerList>(this, ULeapFingerList::StaticClass());
		Private->ExtendedList->SetFlags(RF_RootSet);
	}
	Private->ExtendedList->SetFingerList(Private->Fingers.extended());
	return (Private->ExtendedList);
}

ULeapFinger *ULeapFingerList::Leftmost()
{
	if (Private->Leftmost == NULL)
	{
		Private->Leftmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		Private->Leftmost->SetFlags(RF_RootSet);
	}
	Private->Leftmost->SetFinger(Private->Fingers.leftmost());
	return (Private->Leftmost);
}

ULeapFinger *ULeapFingerList::Rightmost()
{
	if (Private->Rightmost == NULL)
	{
		Private->Rightmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		Private->Rightmost->SetFlags(RF_RootSet);
	}
	Private->Rightmost->SetFinger(Private->Fingers.rightmost());
	return (Private->Rightmost);
}


ULeapFinger *ULeapFingerList::Frontmost()
{
	if (Private->Frontmost == NULL)
	{
		Private->Frontmost = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		Private->Frontmost->SetFlags(RF_RootSet);
	}
	Private->Frontmost->SetFinger(Private->Fingers.frontmost());
	return (Private->Frontmost);
}

ULeapFinger *ULeapFingerList::GetPointableById(int32 Id)
{
	if (Private->PointableById == NULL)
	{
		Private->PointableById = NewObject<ULeapFinger>(this, ULeapFinger::StaticClass());
		//NB: non-temporary so we add it to the rootset and remove it when the object itself gets destroyed. Behaves like a property except allocated only on need.
		//_private->pointableById->SetFlags(RF_DefaultSubObject);	//causes still PIE attachment error
		Private->PointableById->SetFlags(RF_RootSet);
	}
	Private->PointableById->SetFinger(Private->Fingers[Id]);
	return (Private->PointableById);
}

void ULeapFingerList::SetFingerList(const Leap::FingerList &Fingers)
{
	Private->Fingers = Fingers;

	Count = Private->Fingers.count();
	IsEmpty = Private->Fingers.isEmpty();
}

Leap::FingerList* ULeapFingerList::FingerList()
{
	return &(Private->Fingers);
}
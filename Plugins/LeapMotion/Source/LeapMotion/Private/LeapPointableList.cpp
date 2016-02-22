#include "LeapMotionPrivatePCH.h"
#include "LeapPointableList.h"
#include "LeapPointable.h"

class PrivatePointableList
{
public:
	~PrivatePointableList()
	{
		if (!CleanupCalled)
		{
			Cleanup();
		}
	}
	void Cleanup()
	{
		/*if (Frontmost)
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
		CleanupCalled = true;*/
	}
	bool CleanupCalled = false;
	Leap::PointableList Pointables;
	ULeapPointable* Leftmost = NULL;
	ULeapPointable* Rightmost = NULL;
	ULeapPointable* Frontmost = NULL;
	ULeapPointable* PointableById = NULL;
	ULeapPointableList* AppendedList = NULL;
	ULeapPointableList* ExtendedList = NULL;
};

ULeapPointableList::ULeapPointableList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivatePointableList())
{
}

ULeapPointableList::~ULeapPointableList()
{
	delete Private;
}
void ULeapPointableList::CleanupRootReferences()
{
	//Private->Cleanup();
	//this->RemoveFromRoot();
}

ULeapPointableList *ULeapPointableList::Append(ULeapPointableList *List)
{
	if (Private->AppendedList == NULL)
	{
		Private->AppendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		Private->AppendedList->SetFlags(RF_ClassDefaultObject);
	}
	Private->AppendedList->SetPointableList(Private->Pointables.append(List->Private->Pointables));
	return (Private->AppendedList);
}

ULeapPointableList *ULeapPointableList::AppendTools(ULeapToolList *List)
{
	if (Private->AppendedList == NULL)
	{
		Private->AppendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		Private->AppendedList->SetFlags(RF_ClassDefaultObject);
	}
	Private->AppendedList->SetPointableList(this->Private->Pointables.append(*List->ToolList()));
	return (Private->AppendedList);
}

ULeapPointableList *ULeapPointableList::AppendFingers(ULeapFingerList *List)
{
	if (Private->AppendedList == NULL)
	{
		Private->AppendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		Private->AppendedList->SetFlags(RF_ClassDefaultObject);
	}
	Private->AppendedList->SetPointableList(this->Private->Pointables.append(*List->FingerList()));
	return (Private->AppendedList);
}

ULeapPointableList *ULeapPointableList::Extended()
{
	if (Private->ExtendedList == NULL)
	{
		Private->ExtendedList = NewObject<ULeapPointableList>(this, ULeapPointableList::StaticClass());
		Private->ExtendedList->SetFlags(RF_ClassDefaultObject);
	}
	Private->ExtendedList->SetPointableList(Private->Pointables.extended());
	return (Private->ExtendedList);
}

ULeapPointable *ULeapPointableList::Leftmost()
{
	if (Private->Leftmost == NULL)
	{
		Private->Leftmost = NewObject<ULeapPointable>(this);
		Private->Leftmost->SetFlags(RF_ClassDefaultObject);
	}
	Private->Leftmost->SetPointable(Private->Pointables.leftmost());
	return (Private->Leftmost);
}

ULeapPointable *ULeapPointableList::Rightmost()
{
	if (Private->Rightmost == NULL)
	{
		Private->Rightmost = NewObject<ULeapPointable>(this);
		Private->Rightmost->SetFlags(RF_ClassDefaultObject);
	}
	Private->Rightmost->SetPointable(Private->Pointables.rightmost());
	return (Private->Rightmost);
}


ULeapPointable *ULeapPointableList::Frontmost()
{
	if (Private->Frontmost == NULL)
	{
		Private->Frontmost = NewObject<ULeapPointable>(this);
		Private->Frontmost->SetFlags(RF_ClassDefaultObject);
	}
	Private->Frontmost->SetPointable(Private->Pointables.frontmost());
	return (Private->Frontmost);
}

ULeapPointable *ULeapPointableList::GetPointableById(int32 Id)
{
	if (Private->PointableById == NULL)
	{
		Private->PointableById = NewObject<ULeapPointable>(this);
		Private->PointableById->SetFlags(RF_ClassDefaultObject);
	}
	Private->PointableById->SetPointable(Private->Pointables[Id]);
	return (Private->PointableById);
}

void ULeapPointableList::SetPointableList(const Leap::PointableList &Pointables)
{
	Private->Pointables = Pointables;
	Count = Private->Pointables.count();
	IsEmpty = Private->Pointables.isEmpty();
}
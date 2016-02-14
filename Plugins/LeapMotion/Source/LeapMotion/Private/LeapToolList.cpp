#include "LeapMotionPrivatePCH.h"
#include "LeapToolList.h"
#include "LeapTool.h"

class PrivateToolList
{
public:
	~PrivateToolList()
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
		if (PointableById)
		{
			PointableById->CleanupRootReferences();
		}
		if (AppendedList)
		{
			AppendedList->CleanupRootReferences();
		}
		CleanupCalled = true;
	}
	bool CleanupCalled = false;
	Leap::ToolList Tools;
	ULeapTool* Leftmost = NULL;
	ULeapTool* Rightmost = NULL;
	ULeapTool* Frontmost = NULL;
	ULeapTool* PointableById = NULL;
	ULeapToolList* AppendedList = NULL;
};


ULeapToolList::ULeapToolList(const FObjectInitializer &ObjectInitializer) : UObject(ObjectInitializer), Private(new PrivateToolList())
{
}

ULeapToolList::~ULeapToolList()
{
	delete Private;
}
void ULeapToolList::CleanupRootReferences()
{
	Private->Cleanup();
	this->RemoveFromRoot();
}

ULeapToolList *ULeapToolList::Append(const ULeapToolList *List)
{
	if (Private->AppendedList == NULL)
	{
		Private->AppendedList = NewObject<ULeapToolList>(this, ULeapToolList::StaticClass());
		Private->AppendedList->SetFlags(RF_RootSet);
	}
	Private->AppendedList->SetToolList(this->Private->Tools.append(List->Private->Tools));
	return (Private->AppendedList);
}

int32 ULeapToolList::Count() const
{
	return (Private->Tools.count());
}

bool ULeapToolList::IsEmpty() const
{
	return (Private->Tools.isEmpty());
}

ULeapTool* ULeapToolList::Leftmost()
{
	if (Private->Leftmost == NULL)
	{
		Private->Leftmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		Private->Leftmost->SetFlags(RF_RootSet);
	}
	Private->Leftmost->SetTool(Private->Tools.leftmost());
	return (Private->Leftmost);
}

ULeapTool* ULeapToolList::Rightmost()
{
	if (Private->Rightmost == NULL)
	{
		Private->Rightmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		Private->Rightmost->SetFlags(RF_RootSet);
	}
	Private->Rightmost->SetTool(Private->Tools.rightmost());
	return (Private->Rightmost);
}


ULeapTool* ULeapToolList::Frontmost()
{

	if (Private->Frontmost == NULL)
	{
		Private->Frontmost = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		Private->Frontmost->SetFlags(RF_RootSet);
	}
	Private->Frontmost->SetTool(Private->Tools.frontmost());
	return (Private->Frontmost);
}

ULeapPointable* ULeapToolList::GetPointableById(int32 id)
{
	if (Private->PointableById == NULL)
	{
		Private->PointableById = NewObject<ULeapTool>(this, ULeapTool::StaticClass());
		Private->PointableById->SetFlags(RF_RootSet);
	}
	Private->PointableById->SetPointable(Private->Tools[id]);
	return (Private->PointableById);
}

void ULeapToolList::SetToolList(const Leap::ToolList &Pointables)
{
	Private->Tools = Pointables;
}

const Leap::ToolList* ULeapToolList::ToolList()
{
	return &(Private->Tools);
}
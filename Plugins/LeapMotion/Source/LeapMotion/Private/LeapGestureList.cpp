#include "LeapMotionPrivatePCH.h"

class PrivateGestureList
{
public:
	~PrivateGestureList()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (gesture)
			gesture->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::GestureList gestures;
	ULeapGesture* gesture = NULL;
};

ULeapGestureList::ULeapGestureList(const FObjectInitializer &init) : UObject(init), _private(new PrivateGestureList())
{
}

ULeapGestureList::~ULeapGestureList()
{
	delete _private;
}

void ULeapGestureList::CleanupRootReferences()
{
	_private->Cleanup();
	this->RemoveFromRoot();
}

ULeapGesture* ULeapGestureList::getIndex(int32 index)
{
	if (_private->gesture == NULL)
	{
		_private->gesture = NewObject<ULeapGesture>(this, ULeapGesture::StaticClass());
		_private->gesture->SetFlags(RF_RootSet);
	}
	_private->gesture->setGesture(_private->gestures[index]);
	return (_private->gesture);
}

ULeapGesture* ULeapGestureList::operator[](int index)
{
	return getIndex(index);
}

void ULeapGestureList::setGestureList(const Leap::GestureList &GestureList)
{
	_private->gestures = GestureList;

	Count = _private->gestures.count();
	IsEmpty = _private->gestures.isEmpty();
}
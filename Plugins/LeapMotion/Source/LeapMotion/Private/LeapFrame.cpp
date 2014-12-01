#include "LeapMotionPrivatePCH.h"

class PrivateLeapFrame
{
public:

	~PrivateLeapFrame()
	{
		if (!cleanupCalled)
			Cleanup();
	}
	void Cleanup()
	{
		if (hands)
			hands->CleanupRootReferences();
		if (fingers)
			fingers->CleanupRootReferences();
		if (gestures)
			gestures->CleanupRootReferences();
		if (interactionBox)
			interactionBox->CleanupRootReferences();
		if (pointables)
			pointables->CleanupRootReferences();
		if (images)
			images->CleanupRootReferences();
		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::Frame frame;
	ULeapHandList* hands = NULL;
	ULeapFingerList* fingers = NULL;
	ULeapGestureList* gestures = NULL;
	ULeapInteractionBox* interactionBox = NULL;
	ULeapPointableList* pointables = NULL;
	ULeapImageList* images = NULL;
};

ULeapFrame::ULeapFrame(const FPostConstructInitializeProperties &init) : UObject(init), _private(new PrivateLeapFrame())
{
}

ULeapFrame::~ULeapFrame()
{
	delete _private;
}

void ULeapFrame::CleanupRootReferences()
{
	_private->Cleanup();
	if (this->HasAnyFlags(RF_RootSet))
		this->RemoveFromRoot();
}

ULeapHandList* ULeapFrame::Hands()
{
	if (_private->hands == NULL)
	{
		_private->hands = NewObject<ULeapHandList>(this);
		_private->hands->SetFlags(RF_RootSet);
	}
	_private->hands->setHandList(_private->frame.hands());
	return (_private->hands);
}

ULeapFingerList* ULeapFrame::Fingers()
{
	if (_private->fingers == NULL)
	{
		_private->fingers = NewObject<ULeapFingerList>(this);
		_private->fingers->SetFlags(RF_RootSet);
	}
	_private->fingers->setFingerList(_private->frame.fingers());
	return (_private->fingers);
}

ULeapGestureList* ULeapFrame::Gestures()
{
	if (_private->gestures == NULL)
	{
		_private->gestures = NewObject<ULeapGestureList>(this);
		_private->gestures->SetFlags(RF_RootSet);
	}
	_private->gestures->setGestureList(_private->frame.gestures());
	return (_private->gestures);
}

ULeapInteractionBox* ULeapFrame::InteractionBox()
{
	if (_private->interactionBox == NULL)
	{
		_private->interactionBox = NewObject<ULeapInteractionBox>(this);
		_private->interactionBox->SetFlags(RF_RootSet);
	}
	_private->interactionBox->setInteractionBox(_private->frame.interactionBox());
	return (_private->interactionBox);
}

ULeapPointableList* ULeapFrame::Pointables()
{
	if (_private->pointables == NULL)
	{
		_private->pointables = NewObject<ULeapPointableList>(this);
		_private->pointables->SetFlags(RF_RootSet);
	}
	_private->pointables->setPointableList(_private->frame.pointables());
	return (_private->pointables);
}

ULeapImageList* ULeapFrame::Images()
{
	if (_private->images == NULL)
	{
		_private->images = NewObject<ULeapImageList>(this);
		_private->images->SetFlags(RF_RootSet);
	}
	_private->images->setLeapImageList(_private->frame.images());
	return (_private->images);
}

const Leap::Frame &ULeapFrame::getFrame() const
{
	return (_private->frame);
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	Leap::Frame frame = leap.frame(history);
	_private->frame = frame;
	IsValid = _private->frame.isValid();
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_private->frame = frame;
	IsValid = _private->frame.isValid();
}


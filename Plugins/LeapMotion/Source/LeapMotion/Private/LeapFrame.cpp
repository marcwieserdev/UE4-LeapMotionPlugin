#include "LeapMotionPrivatePCH.h"
#include "LeapTool.h"

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
		if (finger)
			finger->CleanupRootReferences();
		if (fingers)
			fingers->CleanupRootReferences();
		if (gesture)
			gesture->CleanupRootReferences();
		if (gestures)
			gestures->CleanupRootReferences();
		if (hand)
			hand->CleanupRootReferences();
		if (hands)
			hands->CleanupRootReferences();
		if (images)
			images->CleanupRootReferences();
		if (interactionBox)
			interactionBox->CleanupRootReferences();
		if (pointable)
			pointable->CleanupRootReferences();
		if (pointables)
			pointables->CleanupRootReferences();
		if (tool)
			tool->CleanupRootReferences();
		if (tools)
			tools->CleanupRootReferences();

		cleanupCalled = true;
	}
	bool cleanupCalled = false;
	Leap::Frame frame;

	ULeapFinger* finger = NULL;
	ULeapFingerList* fingers = NULL;

	ULeapGesture* gesture = NULL;
	ULeapGestureList* gestures = NULL;

	ULeapHand* hand = NULL;
	ULeapHandList* hands = NULL;

	ULeapImageList* images = NULL;
	ULeapInteractionBox* interactionBox = NULL;

	ULeapPointable* pointable = NULL;
	ULeapPointableList* pointables = NULL;

	ULeapTool* tool = NULL;
	ULeapToolList* tools = NULL;
};

ULeapFrame::ULeapFrame(const FObjectInitializer &init) : UObject(init), _private(new PrivateLeapFrame())
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

ULeapFinger* ULeapFrame::Finger(int32 id)
{
	if (_private->finger == NULL)
	{
		_private->finger = NewObject<ULeapFinger>(this);
		_private->finger->SetFlags(RF_RootSet);
	}
	_private->finger->setFinger(_private->frame.finger(id));
	return _private->finger;
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

ULeapGesture* ULeapFrame::Gesture(int32 id)
{
	if (_private->gesture == NULL)
	{
		_private->gesture = NewObject<ULeapGesture>(this);
		_private->gesture->SetFlags(RF_RootSet);
	}
	_private->gesture->setGesture(_private->frame.gesture(id));
	return _private->gesture;
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

ULeapGestureList* ULeapFrame::GesturesSinceFrame(class ULeapFrame* frame)
{
	if (_private->gestures == NULL)
	{
		_private->gestures = NewObject<ULeapGestureList>(this);
		_private->gestures->SetFlags(RF_RootSet);
	}
	_private->gestures->setGestureList(_private->frame.gestures(frame->getFrame()));
	return (_private->gestures);
}

ULeapHand* ULeapFrame::Hand(int32 id)
{
	if (_private->hand == NULL)
	{
		_private->hand = NewObject<ULeapHand>(this);
		_private->hand->SetFlags(RF_RootSet);
	}
	_private->hand->setHand(_private->frame.hand(id));
	return _private->hand;
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

ULeapPointable* ULeapFrame::Pointable(int32 id)
{
	if (_private->pointable == NULL)
	{
		_private->pointable = NewObject<ULeapPointable>(this);
		_private->pointable->SetFlags(RF_RootSet);
	}
	_private->pointable->setPointable(_private->frame.pointable(id));
	return _private->pointable;
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

float ULeapFrame::RotationAngle(class ULeapFrame* frame)
{
	return _private->frame.rotationAngle(frame->getFrame());
}

float ULeapFrame::RotationAngleAroundAxis(class ULeapFrame* frame, FVector axis)
{
	return _private->frame.rotationAngle(frame->getFrame(), convertUEToLeap(axis));
}

FVector ULeapFrame::RotationAxis(class ULeapFrame* frame)
{
	return convertLeapToUE(_private->frame.rotationAxis(frame->getFrame()));
}

float ULeapFrame::RotationProbability(class ULeapFrame* frame)
{
	return _private->frame.rotationProbability(frame->getFrame());
}

float ULeapFrame::ScaleFactor(class ULeapFrame* frame)
{
	return _private->frame.scaleFactor(frame->getFrame());
}

float ULeapFrame::ScaleProbability(class ULeapFrame* frame)
{
	return _private->frame.scaleProbability(frame->getFrame());
}

ULeapTool* ULeapFrame::Tool(int32 id)
{
	if (_private->tool == NULL)
	{
		_private->tool = NewObject<ULeapTool>(this);
		_private->tool->SetFlags(RF_RootSet);
	}
	_private->tool->setTool(_private->frame.tool(id));
	return _private->tool;
}

ULeapToolList* ULeapFrame::Tools()
{
	if (_private->tools == NULL)
	{
		_private->tools = NewObject<ULeapToolList>(this);
		_private->tools->SetFlags(RF_RootSet);
	}
	_private->tools->setToolList(_private->frame.tools());
	return (_private->tools);
}

FVector ULeapFrame::Translation(class ULeapFrame* frame)
{
	return convertLeapToUE(_private->frame.translation(frame->getFrame()));
}

float ULeapFrame::TranslationProbability(class ULeapFrame* frame)
{
	return _private->frame.translationProbability(frame->getFrame());
}

const Leap::Frame &ULeapFrame::getFrame() const
{
	return (_private->frame);
}

void ULeapFrame::setFrame(Leap::Controller &leap, int history)
{
	Leap::Frame frame = leap.frame(history);

	this->setFrame(frame);
}

void ULeapFrame::setFrame(const Leap::Frame &frame)
{
	_private->frame = frame;
	IsValid = _private->frame.isValid();
	CurrentFPS = _private->frame.currentFramesPerSecond();
}


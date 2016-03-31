#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"
#include "SlateBasics.h"

class LeapControllerPrivate
{
public:
	//Reference pointers
	LeapControllerData* ControllerData;
	UObject* CurrentlyUsedDelegate;

	//Functions
	void SetPolicyStatus(Leap::Controller::PolicyFlag Flag, bool Status);
	void SetPolicyFlagsFromBools();
};

//LeapControllerPrivate
void LeapControllerPrivate::SetPolicyStatus(Leap::Controller::PolicyFlag Flag, bool Status)
{
	if (Status)
	{
		ControllerData->LeapController.setPolicy(Flag);
	}
	else
	{
		ControllerData->LeapController.clearPolicy(Flag);
	}
}

void LeapControllerPrivate::SetPolicyFlagsFromBools()
{
	SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_OPTIMIZE_HMD, ControllerData->bOptimizeForHMD);
	SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_IMAGES, ControllerData->bAllowImageEvents);
}

//ULeapController
ULeapController::ULeapController(const FObjectInitializer &ObjectInitializer) : UActorComponent(ObjectInitializer), Private(new LeapControllerPrivate())
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to
}

ULeapController::~ULeapController()
{
	delete Private;
}

bool ULeapController::IsConnected() const
{
	return Private->ControllerData->LeapController.isConnected();
}

void ULeapController::OnRegister()
{
	Super::OnRegister();

	SetInterfaceDelegate(GetOwner());

	//Grab our data pointers
	Private->ControllerData = ILeapMotionPlugin::Get().ControllerData();
}

void ULeapController::OnUnregister()
{
	if (Private->CurrentlyUsedDelegate != nullptr)
	{
		ILeapMotionPlugin::Get().RemoveEventDelegate(Private->CurrentlyUsedDelegate);
	}
	Private->CurrentlyUsedDelegate = nullptr;

	Super::OnUnregister();
	//UE_LOG(LeapPluginLog, Log, TEXT("Unregistered Leap Component(%d)."), controllerCount);
}

void ULeapController::TickComponent(float DeltaTime, enum ELevelTick TickType,
									FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ULeapFrame* ULeapController::Frame(int32 History)
{
	if (PFrame == nullptr)
	{
		PFrame = NewObject<ULeapFrame>(this, ULeapFrame::StaticClass());
	}
	PFrame->SetFrame(Private->ControllerData->LeapController, History);
	return (PFrame);
}

bool ULeapController::HasFocus() const
{
	return (Private->ControllerData->LeapController.hasFocus());
}

bool ULeapController::IsServiceConnected() const
{
	return (Private->ControllerData->LeapController.isServiceConnected());
}


void ULeapController::OptimizeForHMD(bool useTopdown, bool autoRotate, bool autoShift)
{
	//Set Policy Optimization
	Private->ControllerData->bOptimizeForHMD = useTopdown;
	Private->SetPolicyFlagsFromBools();

	//Pass adjustment booleans
	if (useTopdown)
	{
		LeapSetShouldAdjustForFacing(true);
	}
	else
	{
		LeapSetShouldAdjustForFacing(false);
	}

	LeapSetShouldAdjustForHMD(autoRotate, autoShift);
	LeapSetShouldAdjustForMountOffset(Private->ControllerData->bUseMountOffset);	//this function defaults to true at the moment, can be changed via command
}

void ULeapController::EnableImageSupport(bool allowImages, bool emitImageEvents, bool useGammaCorrection)
{
	Private->ControllerData->bUseGammaCorrection = useGammaCorrection;
	Private->ControllerData->bAllowImageEvents = allowImages;
	Private->SetPolicyFlagsFromBools();
	Private->ControllerData->bImageEventsEnabled = emitImageEvents;
}

void ULeapController::EnableBackgroundTracking(bool trackInBackground)
{
	Private->SetPolicyStatus(Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES, trackInBackground);
}

void ULeapController::EnableGesture(LeapGestureType type, bool enable)
{
	Leap::Gesture::Type rawType;

	switch (type)
	{
	case GESTURE_TYPE_CIRCLE:
		rawType = Leap::Gesture::TYPE_CIRCLE;
		break;
	case GESTURE_TYPE_KEY_TAP:
		rawType = Leap::Gesture::TYPE_KEY_TAP;
		break;
	case GESTURE_TYPE_SCREEN_TAP:
		rawType = Leap::Gesture::TYPE_SCREEN_TAP;
		break;
	case GESTURE_TYPE_SWIPE:
		rawType = Leap::Gesture::TYPE_SWIPE;
		break;
	default:
		rawType = Leap::Gesture::TYPE_INVALID;
		break;
	}

	Private->ControllerData->LeapController.enableGesture(rawType, enable);
}

void ULeapController::SetLeapMountToHMDOffset(FVector Offset)
{
	if (Offset == FVector(0, 0, 0))
	{
		Private->ControllerData->bUseMountOffset = false;
		LeapSetShouldAdjustForMountOffset(Private->ControllerData->bUseMountOffset);
	}
	else
	{
		Private->ControllerData->bUseMountOffset = true;
		LeapSetShouldAdjustForMountOffset(Private->ControllerData->bUseMountOffset);
		LeapSetMountToHMDOffset(Offset);
	}
}

//Leap Event Interface - Event Driven System
void ULeapController::SetInterfaceDelegate(UObject* NewDelegate)
{
	UE_LOG(LeapPluginLog, Log, TEXT("InterfaceDelegate: %s"), *NewDelegate->GetName());

	//Use this format to support both blueprint and C++ form
	if (NewDelegate->GetClass()->ImplementsInterface(ULeapEventInterface::StaticClass()))
	{
		Private->CurrentlyUsedDelegate = NewDelegate;	//reference our delegate so we can remove it later
		ILeapMotionPlugin::Get().AddEventDelegate(Private->CurrentlyUsedDelegate);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("LeapController Warning: Delegate is NOT set, did you implement LeapEventInterface?"));
	}
}

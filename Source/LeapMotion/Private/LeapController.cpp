#include "LeapMotionPrivatePCH.h"

ULeapController::ULeapController(const FPostConstructInitializeProperties &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
}

ULeapController::~ULeapController()
{
}

bool ULeapController::isConnected() const
{
	return _leap.isConnected();
}

void ULeapController::InitializeComponent()
{
	Super::InitializeComponent();
}

void ULeapController::TickComponent(float DeltaTime, enum ELevelTick TickType,
									FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULeapController::BeginDestroy()
{
	Super::BeginDestroy();
}

const Leap::Controller &ULeapController::getData() const
{
	return (_leap);
}

ULeapFrame *ULeapController::getFrame(int32 history)
{
	ULeapFrame *rframe;


	rframe = ConstructObject<ULeapFrame>(ULeapFrame::StaticClass());
	rframe->setFrame(_leap, history);
	return (rframe);
}

bool ULeapController::hasFocus() const
{
	return (_leap.hasFocus());
}

bool ULeapController::isServiceConnected() const
{
	return (_leap.isServiceConnected());
}

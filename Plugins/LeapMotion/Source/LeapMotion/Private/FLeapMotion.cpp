#include "LeapMotionPrivatePCH.h"

void FLeapMotion::StartupModule()
{

}

void FLeapMotion::ShutdownModule()
{

}

Leap::Controller* FLeapMotion::Controller()
{
	return &LeapController;
}

IMPLEMENT_MODULE(FLeapMotion, LeapMotion)
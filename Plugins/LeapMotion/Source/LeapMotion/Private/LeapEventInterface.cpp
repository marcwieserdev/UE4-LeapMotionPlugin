#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"


ULeapEventInterface::ULeapEventInterface(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

FString ILeapEventInterface::ToString()
{
	return "ILeapEventInterface::ToString()";
}
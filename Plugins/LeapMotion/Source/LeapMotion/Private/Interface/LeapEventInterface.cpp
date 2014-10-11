#include "LeapMotionPrivatePCH.h"
#include "LeapEventInterface.h"


ULeapEventInterface::ULeapEventInterface(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

//This is required for compiling, would also let you know if somehow you called
//the base event/function rather than the over-rided version
FString ILeapEventInterface::ToString()
{
	return "ILeapEventInterface::ToString()";
}
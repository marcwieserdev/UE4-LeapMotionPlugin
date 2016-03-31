#pragma once

#include "LeapMotionPublicPCH.h"
#include "LeapBaseObject.generated.h"

/**
* Optional base class for custom memory management
*/
UCLASS()
class LEAPMOTION_API ULeapBaseObject : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	virtual void CleanupRootReferences() {};
};
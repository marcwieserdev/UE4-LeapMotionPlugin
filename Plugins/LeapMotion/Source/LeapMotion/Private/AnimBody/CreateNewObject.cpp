//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#include "LeapMotionPrivatePCH.h"
#include "CreateNewObject.h"

UCreateNewObject::UCreateNewObject(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

UObject* UCreateNewObject::NewObjectFromBlueprint(UObject* WorldContextObject, TSubclassOf<UObject> UC)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UObject* tempObject = StaticConstructObject(UC);

	return tempObject;
}
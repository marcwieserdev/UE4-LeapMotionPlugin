//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "CreateNewObject.generated.h"

UCLASS()
class UCreateNewObject : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

		UFUNCTION(BlueprintPure, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", FriendlyName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
		static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, TSubclassOf<UObject> UC);
};
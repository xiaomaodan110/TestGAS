#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "TestGASComponentBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTGAS_API UTestGASComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UTestGASComponentBase();
};
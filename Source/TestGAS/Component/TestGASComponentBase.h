#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Components/GameFrameworkComponent.h"

#include "TestGASComponentBase.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTGAS_API UTestGASComponentBase : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UTestGASComponentBase(const FObjectInitializer& ObjectInitializer);
};
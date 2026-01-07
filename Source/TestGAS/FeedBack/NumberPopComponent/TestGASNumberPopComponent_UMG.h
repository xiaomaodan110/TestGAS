#pragma once

#include "Components/ControllerComponent.h"
#include "GameplayTagContainer.h"
#include "TestGASNumberPopComponent.h"

#include "TestGASNumberPopComponent_UMG.generated.h"

class ATestGASDamageNumActor;

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class UTestGASNumberPopComponent_UMG : public UTestGASNumberPopComponent {
	GENERATED_BODY()

public:
	UTestGASNumberPopComponent_UMG(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void AddNumberPop(const FTestGASNumberPopRequest& NewRequest);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TestGAS|DamageNum", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATestGASDamageNumActor> NumPopActorClass;
};
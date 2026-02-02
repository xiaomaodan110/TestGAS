#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "TestGASDamageExecution_Air.generated.h"


UCLASS()
class UTestGASDamageExecution_Air : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UTestGASDamageExecution_Air();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "TestGASDamageExecution.generated.h"


UCLASS()
class UTestGASDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UTestGASDamageExecution();

protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
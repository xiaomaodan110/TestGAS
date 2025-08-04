// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemComponent.h"

#include "TestGASAbilitySystemComponent.generated.h"

UCLASS()
class TESTGAS_API UTestGASAbilitySystemComponent : public UAbilitySystemComponent {

	GENERATED_BODY()

public:

	UTestGASAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();


protected:
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;


protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};

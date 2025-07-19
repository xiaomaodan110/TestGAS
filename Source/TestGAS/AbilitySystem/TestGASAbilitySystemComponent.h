// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemComponent.h"

#include "TestGASAbilitySystemComponent.generated.h"

UCLASS()
class TESTGAS_API UTestGASAbilitySystemComponent : public UAbilitySystemComponent {

	GENERATED_BODY();

public:

	UTestGASAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

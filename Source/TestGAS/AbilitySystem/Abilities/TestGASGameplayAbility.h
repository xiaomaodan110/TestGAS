#pragma once

#include "Abilities/GameplayAbility.h"

#include "TestGASGameplayAbility.generated.h"

class UTestGASAbilitySystemComponent;
class ATestGASCharacterBase;
class ATestGASPlayerController;

UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by this project"))
class TESTGAS_API UTestGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTestGASGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	UTestGASAbilitySystemComponent* GetTestGASAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	ATestGASPlayerController* GetTestGASPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	ATestGASCharacterBase* GetTestGASCharacterFromActorInfo() const;


};
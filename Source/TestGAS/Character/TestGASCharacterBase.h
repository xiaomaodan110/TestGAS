#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayAbilitySpecHandle.h"

#include "TestGASCharacterBase.generated.h"

class ATestGASPlayerState;
class ATestGASPlayerController;
class UTestGASAbilitySystemComponent;
class UTestGASGameplayAbility;
class UTestGASComboComponent;

UCLASS(config = Game)
class TESTGAS_API ATestGASCharacterBase : public ACharacter, public IAbilitySystemInterface, public IGameplayCueInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ATestGASCharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Character")
	ATestGASPlayerController* GetTestGASPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Character")
	ATestGASPlayerState* GetTestGASPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Character")
	FORCEINLINE UTestGASAbilitySystemComponent* GetTestGASAbilitySystemComponent() const { return AbilitySystemComponent; };

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Character")
	FORCEINLINE UTestGASComboComponent* GetTestGASComboComponent() const { return ComboComponent; };

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


protected:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "TestGAS|Ability", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TSubclassOf<UTestGASGameplayAbility>> AbilitiesToAdd;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitiesToActive;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const class UTestGASCharacterAttributeSet> CharacterSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASComboComponent> ComboComponent;
};
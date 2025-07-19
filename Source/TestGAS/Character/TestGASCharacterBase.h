#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "GameplayCueInterface.h"
#include "GameplayTagAssetInterface.h"

#include "TestGASCharacterBase.generated.h"

class ATestGASPlayerState;
class ATestGASPlayerController;
class UTestGASAbilitySystemComponent;


UCLASS(config = Game)
class TESTGAS_API ATestGASCharacterBase : public ACharacter, public IAbilitySystemInterface, public IGameplayCueInterface,  public IGameplayTagAssetInterface
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintCallable, Category = "TestGAS|Character")
	ATestGASPlayerState* GetTestGASPlayerState() const;

	UPROPERTY(BlueprintCallable, Category = "TestGAS|Character")
	ATestGASPlayerController* GetTestGASPlayerController() const;

	UPROPERTY(BlueprintCallable, Category = "TestGAS|Character")
	FORCEINLINE UTestGASAbilitySystemComponent* GetTestGASAbilitySystemComponent() const { return AbilitySystemComponent; };


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASAbilitySystemComponent> AbilitySystemComponent;
};
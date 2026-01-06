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
class UTestGASHealthComponent;


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

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Character")
	FORCEINLINE UTestGASHealthComponent* GetTestGASHealthComponent() const { return HealthComponent; };

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);


	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UninitAndDestroy();

	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeathFinished"))
	void K2_OnDeathFinished();

protected:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "TestGAS|Ability", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, TSubclassOf<UTestGASGameplayAbility>> AbilitiesToAdd;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitiesToActive;


	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "TestGAS|Ability", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UTestGASGameplayAbility> DeathAbilityClass;

	FGameplayAbilitySpecHandle DeathAbilityHandle;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const class UTestGASCharacterAttributeSet> CharacterSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASComboComponent> ComboComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TestGAS|Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTestGASHealthComponent> HealthComponent;
};
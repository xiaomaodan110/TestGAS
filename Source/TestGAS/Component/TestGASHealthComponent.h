#pragma once

#include "CoreMinimal.h"

#include "TestGASComponentBase.h"

#include "NativeGameplayTags.h"

#include "TestGASHealthComponent.generated.h"


class UTestGASHealthComponent;
class UTestGASAbilitySystemComponent;
class UTestGASCharacterAttributeSet;

class UObject;
struct FFrame;
struct FGameplayEffectSpec;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestGASHealth_DeathEvent, AActor*, OwningActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTestGASHealth_AttributeChanged, UTestGASHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

TESTGAS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_Damage);
TESTGAS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageImmunity);
TESTGAS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_DamageSelfDestruct);
TESTGAS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_FellOutOfWorld);
TESTGAS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TestGAS_Damage_Message);

UENUM(BlueprintType)
enum class ETestGASDeathState : uint8 {
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class TESTGAS_API UTestGASHealthComponent : public UTestGASComponentBase {
	GENERATED_BODY()

public:
	UTestGASHealthComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "TestGAS|Health")
	static UTestGASHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UTestGASHealthComponent>() : nullptr); }

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	void InitializeWithAbilitySystem(UTestGASAbilitySystemComponent* InASC);

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	void UninitializeFromAbilitySystem();

	// Returns the current health value.
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetHealth() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetMaxHealth() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetHealthNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetMana() const;

	// Returns the current maximum health value.
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetMaxMana() const;

	// Returns the current health in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	float GetManaNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Health")
	ETestGASDeathState GetDeathState() const { return DeathState; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "TestGAS|Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const { return (DeathState > ETestGASDeathState::NotDead); }

	// Begins the death sequence for the owner.
	virtual void StartDeath();

	// Ends the death sequence for the owner.
	virtual void FinishDeath();

	// Applies enough damage to kill the owner.
	virtual void DamageSelfDestruct(bool bFellOutOfWorld = false);


public:

	// Delegate fired when the health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_AttributeChanged OnHealthChanged;

	// Delegate fired when the max health value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_AttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_AttributeChanged OnManaChanged;

	// Delegate fired when the max mana value has changed. This is called on the client but the instigator may not be valid
	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_AttributeChanged OnMaxManaChanged;

	// Delegate fired when the death sequence has started.
	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_DeathEvent OnDeathStarted;

	// Delegate fired when the death sequence has finished.
	UPROPERTY(BlueprintAssignable)
	FTestGASHealth_DeathEvent OnDeathFinished;
protected:

	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	virtual void HandleManaChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);
	virtual void HandleMaxManaChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue);

	UFUNCTION()
	virtual void OnRep_DeathState(ETestGASDeathState OldDeathState);

protected:
	// Ability system used by this component.
	UPROPERTY()
	TObjectPtr<UTestGASAbilitySystemComponent> AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	TObjectPtr<const UTestGASCharacterAttributeSet> HealthSet;

	UPROPERTY(ReplicatedUsing = OnRep_DeathState)
	ETestGASDeathState DeathState;
};
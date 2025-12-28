#pragma once

#include "CoreMinimal.h"
#include "TestGASAttributeSet.h"

#include "TestGASCharacterAttributeSet.generated.h"

UCLASS()

class TESTGAS_API UTestGASCharacterAttributeSet : public UTestGASAttributeSet
{
	GENERATED_BODY()

public:
	UTestGASCharacterAttributeSet();

	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Level);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Attack);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Defense);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, Exp);
	ATTRIBUTE_ACCESSORS(UTestGASCharacterAttributeSet, MaxExp);


	mutable FTestGASAttributeEvent OnHealthChanged;
	mutable FTestGASAttributeEvent OnMaxHealthChanged;
	mutable FTestGASAttributeEvent OnOutOfHealth;
	mutable FTestGASAttributeEvent OnManaChanged;
	mutable FTestGASAttributeEvent OnMaxManaChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Exp(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxExp(const FGameplayAttributeData& OldValue);


	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Damage, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Level, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Level;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Health, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_MaxHealth, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	bool bOutOfHealth;
	float HealthBeforeAttributeChange;
	float MaxHealthBeforeAttributeChange;
	float MaxManaBeforeAttributeChange;
	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Mana, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_MaxMana, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Stamina, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_MaxStamina, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Attack, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Attack;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Defense, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Defense;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_Exp, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData Exp;

	UPROPERTY(BlueprintReadOnly, Category = "TestGAS|Attribute", ReplicatedUsing = OnRep_MaxExp, meta = (HideFromModifiers, AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxExp;
};
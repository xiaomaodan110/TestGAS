#include "UI_CharacterInfo.h"

#include "TestGASCharacterBase.h"
#include "TestGASCharacterAttributeSet.h"
#include "TestGASAbilitySystemComponent.h"

#include "Components/TextBlock.h"

// must super!!!
void UUI_CharacterInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_CharacterInfo::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_CharacterInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (ATestGASCharacterBase* InCharacter = UI_GetTestGASCharacterBase()) {
		if (UTestGASAbilitySystemComponent* InASC = InCharacter->GetTestGASAbilitySystemComponent()) {
			if (const UTestGASCharacterAttributeSet* InAttributeSet = Cast<UTestGASCharacterAttributeSet>(InASC->GetAttributeSet(UTestGASCharacterAttributeSet::StaticClass()))) {
				if (Health) {
					float HealthNum = InAttributeSet->GetHealth();
					float MaxHealthNum = InAttributeSet->GetMaxHealth();
					FString HealthStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(HealthNum));
					FString MaxHealthStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxHealthNum));

					Health->SetText(FText::FromString(HealthStr + "/" + MaxHealthStr));
				}

				if (Mana) {
					float ManaNum = InAttributeSet->GetMana();
					float MaxManaNum = InAttributeSet->GetMaxMana();
					FString ManaStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(ManaNum));
					FString MaxManaStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxManaNum));

					Mana->SetText(FText::FromString(ManaStr + "/" + MaxManaStr));
				}
				if (Stamina) {
					float StaminaNum = InAttributeSet->GetStamina();
					float MaxStaminaNum = InAttributeSet->GetMaxStamina();
					FString StaminaStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(StaminaNum));
					FString MaxStaminaStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxStaminaNum));

					Stamina->SetText(FText::FromString(StaminaStr + "/" + MaxStaminaStr));
				}
				if (Attack) {
					float AttackNum = InAttributeSet->GetAttack();
					FString AttackStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(AttackNum));
					Attack->SetText(FText::FromString(AttackStr));
				}
				if (Defense) {
					float DefenseNum = InAttributeSet->GetDefense();
					FString DefenseStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(DefenseNum));
					Defense->SetText(FText::FromString(DefenseStr));
				}
				if (Exp) {
					float ExpNum = InAttributeSet->GetExp();
					float MaxExpNum = InAttributeSet->GetMaxExp();
					FString ExpStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(ExpNum));
					FString MaxExpStr = FString::Printf(TEXT("%s"), *FString::SanitizeFloat(MaxExpNum));

					Exp->SetText(FText::FromString(ExpStr + "/" + MaxExpStr));
				}
			}
		}
	}
}


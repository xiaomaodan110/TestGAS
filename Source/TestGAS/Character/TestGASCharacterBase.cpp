#include "TestGASCharacterBase.h"

#include "TestGASPlayerController.h"
#include "TestGASPlayerState.h"
#include "TestGASAbilitySystemComponent.h"
#include "TestGASGameplayAbility.h"
#include "TestGASCharacterAttributeSet.h"

#include "TestGASComboComponent.h"

ATestGASPlayerState* ATestGASCharacterBase::GetTestGASPlayerState() const
{
	return CastChecked<ATestGASPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

ATestGASCharacterBase::ATestGASCharacterBase(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UTestGASAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CharacterSet = CreateDefaultSubobject<UTestGASCharacterAttributeSet>(TEXT("CharacterSet"));

	ComboComponent = CreateDefaultSubobject<UTestGASComboComponent>(TEXT("ComboComponent"));
	ComboComponent->SetIsReplicated(false);

	NetUpdateFrequency = 100.0f;
}

ATestGASPlayerController* ATestGASCharacterBase::GetTestGASPlayerController() const
{
	return CastChecked<ATestGASPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

UAbilitySystemComponent* ATestGASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATestGASCharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UTestGASAbilitySystemComponent* TestGASASC = GetTestGASAbilitySystemComponent()) {
		TestGASASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool ATestGASCharacterBase::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return false;
}

bool ATestGASCharacterBase::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

bool ATestGASCharacterBase::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return false;
}

void ATestGASCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority) {
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// temp register abilities
		for (auto& TmpAbilityPair: AbilitiesToAdd) {
			UTestGASGameplayAbility* AbilityCDO = TmpAbilityPair.Value->GetDefaultObject<UTestGASGameplayAbility>();
			FGameplayAbilitySpec AbilitySpec(AbilityCDO, 1);

			AbilitySpec.SourceObject = this;
			AbilitySpec.DynamicAbilityTags.AddTag(TmpAbilityPair.Key);

			const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);

			AbilitiesToActive.Add(TmpAbilityPair.Key, AbilitySpecHandle);
		}
	}
}

void ATestGASCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

#include "TestGASCharacterBase.h"

#include "TestGASPlayerController.h"
#include "TestGASPlayerState.h"
#include "TestGASAbilitySystemComponent.h"

ATestGASPlayerState* ATestGASCharacterBase::GetTestGASPlayerState() const
{
	return CastChecked<ATestGASPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
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
	}
}

void ATestGASCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

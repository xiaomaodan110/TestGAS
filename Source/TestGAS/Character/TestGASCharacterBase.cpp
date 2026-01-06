#include "TestGASCharacterBase.h"

#include "GameFrameWork/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "TestGASPlayerController.h"
#include "TestGASPlayerState.h"
#include "TestGASAbilitySystemComponent.h"
#include "TestGASGameplayAbility.h"
#include "TestGASCharacterAttributeSet.h"

#include "TestGASComboComponent.h"
#include "TestGASHealthComponent.h"

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

	HealthComponent = CreateDefaultSubobject<UTestGASHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
	HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);


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

		UTestGASGameplayAbility* DeathAbilityCDO = DeathAbilityClass->GetDefaultObject<UTestGASGameplayAbility>();
		FGameplayAbilitySpec DeathAbilityCDOSpec(DeathAbilityCDO, 1);
		DeathAbilityCDOSpec.SourceObject = this;
		DeathAbilityHandle = AbilitySystemComponent->GiveAbility(DeathAbilityCDOSpec);
	}

	if (HealthComponent) {
		HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
	}
}

void ATestGASCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority) {
		AbilitySystemComponent->ClearAllAbilities();
	}

	Super::EndPlay(EndPlayReason);
}

void ATestGASCharacterBase::OnDeathStarted(AActor* OwningActor)
{
	DisableMovementAndCollision();

}

void ATestGASCharacterBase::OnDeathFinished(AActor* OwningActor)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}


void ATestGASCharacterBase::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	UCharacterMovementComponent* MoveComp = CastChecked<UCharacterMovementComponent>(GetCharacterMovement());
	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();
}

void ATestGASCharacterBase::DestroyDueToDeath()
{
	K2_OnDeathFinished();

	UninitAndDestroy();
}


void ATestGASCharacterBase::UninitAndDestroy()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		DetachFromControllerPendingDestroy();
		SetLifeSpan(0.1f);
	}

	HealthComponent->UninitializeFromAbilitySystem();

	SetActorHiddenInGame(true);
}
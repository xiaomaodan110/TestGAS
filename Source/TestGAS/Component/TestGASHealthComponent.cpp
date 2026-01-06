#include "TestGASHealthComponent.h"
#include "Net/UnrealNetwork.h"

#include "TestGASLogChannels.h"
#include "TestGASGameplayTag.h"

#include "TestGASAbilitySystemComponent.h"
#include "TestGASCharacterAttributeSet.h"
#include "TestGASGameplayAbility.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Damage, "Gameplay.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageImmunity, "Gameplay.DamageImmunity");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageSelfDestruct, "Gameplay.Damage.SelfDestruct");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_FellOutOfWorld, "Gameplay.Damage.FellOutOfWorld");
UE_DEFINE_GAMEPLAY_TAG(TAG_TestGAS_Damage_Message, "TestGAS.Damage.Message");

UTestGASHealthComponent::UTestGASHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
	DeathState = ETestGASDeathState::NotDead;
}

void UTestGASHealthComponent::InitializeWithAbilitySystem(UTestGASAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<UTestGASCharacterAttributeSet>();
	if (!HealthSet)
	{
		UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);
	HealthSet->OnManaChanged.AddUObject(this, &ThisClass::HandleManaChanged);
	HealthSet->OnMaxManaChanged.AddUObject(this, &ThisClass::HandleMaxManaChanged);

	// TEMP: Reset attributes to default values.  Eventually this will be driven by a spread sheet.
	AbilitySystemComponent->SetNumericAttributeBase(UTestGASCharacterAttributeSet::GetHealthAttribute(), HealthSet->GetMaxHealth());

	ClearGameplayTags();

	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);

	OnManaChanged.Broadcast(this, HealthSet->GetMana(), HealthSet->GetMana(), nullptr);
	OnMaxManaChanged.Broadcast(this, HealthSet->GetMana(), HealthSet->GetMana(), nullptr);
}

void UTestGASHealthComponent::UninitializeFromAbilitySystem()
{
	ClearGameplayTags();

	if (HealthSet)
	{
		HealthSet->OnHealthChanged.RemoveAll(this);
		HealthSet->OnMaxHealthChanged.RemoveAll(this);
		HealthSet->OnManaChanged.RemoveAll(this);
		HealthSet->OnMaxManaChanged.RemoveAll(this);
		HealthSet->OnOutOfHealth.RemoveAll(this);
	}

	HealthSet = nullptr;
	AbilitySystemComponent = nullptr;

}

void UTestGASHealthComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();

	Super::OnUnregister();
}

void UTestGASHealthComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(TestGASGameplayTags::Status_Death_Dying, 0);
		AbilitySystemComponent->SetLooseGameplayTagCount(TestGASGameplayTags::Status_Death_Dead, 0);
	}
}

void UTestGASHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTestGASHealthComponent, DeathState);
}


float UTestGASHealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);
}

float UTestGASHealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);
}

float UTestGASHealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();

		return ((MaxHealth > 0.0f) ? (Health / MaxHealth) : 0.0f);
	}

	return 0.0f;
}

float UTestGASHealthComponent::GetMana() const
{
	return (HealthSet ? HealthSet->GetMana() : 0.0f);

}

float UTestGASHealthComponent::GetMaxMana() const
{
	return (HealthSet ? HealthSet->GetMaxMana() : 0.0f);

}

float UTestGASHealthComponent::GetManaNormalized() const
{
	if (HealthSet)
	{
		const float Mana = HealthSet->GetMana();
		const float MaxMana = HealthSet->GetMaxMana();

		return ((MaxMana > 0.0f) ? (Mana / MaxMana) : 0.0f);
	}

	return 0.0f;
}

void UTestGASHealthComponent::StartDeath()
{
	if (DeathState != ETestGASDeathState::NotDead)
	{
		return;
	}

	DeathState = ETestGASDeathState::DeathStarted;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(TestGASGameplayTags::Status_Death_Dying, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathStarted.Broadcast(Owner);

	Owner->ForceNetUpdate();
}

void UTestGASHealthComponent::FinishDeath()
{
	if (DeathState != ETestGASDeathState::DeathStarted)
	{
		return;
	}

	DeathState = ETestGASDeathState::DeathFinished;

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetLooseGameplayTagCount(TestGASGameplayTags::Status_Death_Dead, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathFinished.Broadcast(Owner);

	Owner->ForceNetUpdate();
}

void UTestGASHealthComponent::DamageSelfDestruct(bool bFellOutOfWorld /*= false*/)
{
	//if ((DeathState == ETestGASDeathState::NotDead) && AbilitySystemComponent)
	//{
	//	const TSubclassOf<UGameplayEffect> DamageGE = UTestGASAssetManager::GetSubclass(UTestGASGameData::Get().DamageGameplayEffect_SetByCaller);
	//	if (!DamageGE)
	//	{
	//		UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: DamageSelfDestruct failed for owner [%s]. Unable to find gameplay effect [%s]."), *GetNameSafe(GetOwner()), *UTestGASGameData::Get().DamageGameplayEffect_SetByCaller.GetAssetName());
	//		return;
	//	}

	//	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageGE, 1.0f, AbilitySystemComponent->MakeEffectContext());
	//	FGameplayEffectSpec* Spec = SpecHandle.Data.Get();

	//	if (!Spec)
	//	{
	//		UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: DamageSelfDestruct failed for owner [%s]. Unable to make outgoing spec for [%s]."), *GetNameSafe(GetOwner()), *GetNameSafe(DamageGE));
	//		return;
	//	}

	//	Spec->AddDynamicAssetTag(TAG_Gameplay_DamageSelfDestruct);

	//	if (bFellOutOfWorld)
	//	{
	//		Spec->AddDynamicAssetTag(TAG_Gameplay_FellOutOfWorld);
	//	}

	//	const float DamageAmount = GetMaxHealth();

	//	Spec->SetSetByCallerMagnitude(TestGASGameplayTags::SetByCaller_Damage, DamageAmount);
	//	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec);
	//}
}

void UTestGASHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UTestGASHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UTestGASHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
#if WITH_SERVER_CODE
	if (AbilitySystemComponent && DamageEffectSpec)
	{
		// Send the "GameplayEvent.Death" gameplay event through the owner's ability system.  This can be used to trigger a death gameplay ability.
		{
			FGameplayEventData Payload;
			Payload.EventTag = TestGASGameplayTags::GameplayEvent_Death;
			Payload.Instigator = DamageInstigator;
			Payload.Target = AbilitySystemComponent->GetAvatarActor();
			Payload.OptionalObject = DamageEffectSpec->Def;
			Payload.ContextHandle = DamageEffectSpec->GetEffectContext();
			Payload.InstigatorTags = *DamageEffectSpec->CapturedSourceTags.GetAggregatedTags();
			Payload.TargetTags = *DamageEffectSpec->CapturedTargetTags.GetAggregatedTags();
			Payload.EventMagnitude = DamageMagnitude;

			FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
			AbilitySystemComponent->HandleGameplayEvent(Payload.EventTag, &Payload);
		}

		// from lyra.
		// Send a standardized verb message that other systems can observe
		{
			//FTestGASVerbMessage Message;
			//Message.Verb = TAG_TestGAS_Elimination_Message;
			//Message.Instigator = DamageInstigator;
			//Message.InstigatorTags = *DamageEffectSpec->CapturedSourceTags.GetAggregatedTags();
			//Message.Target = UTestGASVerbMessageHelpers::GetPlayerStateFromObject(AbilitySystemComponent->GetAvatarActor());
			//Message.TargetTags = *DamageEffectSpec->CapturedTargetTags.GetAggregatedTags();
			////@TODO: Fill out context tags, and any non-ability-system source/instigator tags
			////@TODO: Determine if it's an opposing team kill, self-own, team kill, etc...

			//UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
			//MessageSystem.BroadcastMessage(Message.Verb, Message);
		}

		//@TODO: assist messages (could compute from damage dealt elsewhere)?
	}

#endif // #if WITH_SERVER_CODE
}

void UTestGASHealthComponent::HandleManaChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnManaChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UTestGASHealthComponent::HandleMaxManaChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxManaChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void UTestGASHealthComponent::OnRep_DeathState(ETestGASDeathState OldDeathState)
{
	const ETestGASDeathState NewDeathState = DeathState;

	// Revert the death state for now since we rely on StartDeath and FinishDeath to change it.
	DeathState = OldDeathState;

	if (OldDeathState > NewDeathState)
	{
		// The server is trying to set us back but we've already predicted past the server state.
		UE_LOG(LogTestGAS, Warning, TEXT("TestGASHealthComponent: Predicted past server death state [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		return;
	}

	if (OldDeathState == ETestGASDeathState::NotDead)
	{
		if (NewDeathState == ETestGASDeathState::DeathStarted)
		{
			StartDeath();
		}
		else if (NewDeathState == ETestGASDeathState::DeathFinished)
		{
			StartDeath();
			FinishDeath();
		}
		else
		{
			UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: Invalid death transition [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		}
	}
	else if (OldDeathState == ETestGASDeathState::DeathStarted)
	{
		if (NewDeathState == ETestGASDeathState::DeathFinished)
		{
			FinishDeath();
		}
		else
		{
			UE_LOG(LogTestGAS, Error, TEXT("TestGASHealthComponent: Invalid death transition [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		}
	}

	ensureMsgf((DeathState == NewDeathState), TEXT("TestGASHealthComponent: Death transition failed [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
}


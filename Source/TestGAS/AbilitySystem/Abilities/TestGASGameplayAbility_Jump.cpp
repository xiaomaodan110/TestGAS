
#include "TestGASGameplayAbility_Jump.h"
#include "TestGASCharacter.h"


UTestGASGameplayAbility_Jump::UTestGASGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/):Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UTestGASGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags /* = nullptr */, const FGameplayTagContainer* TargetTags /* = nullptr */, OUT FGameplayTagContainer* OptionalRelevantTags /* = nullptr */) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid()) {
		return false;
	}

	const ATestGASCharacterBase* TestGASCharacter = Cast<ATestGASCharacterBase>(ActorInfo->AvatarActor.Get());

	if (!TestGASCharacter || !TestGASCharacter->CanJump()) {
		return false;
	}

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) {
		return false;
	}

	return true;
}

void UTestGASGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CharacterJumpStop();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UTestGASGameplayAbility_Jump::CharacterJumpStart()
{
	if (ATestGASCharacterBase* TestGASCharacter = GetTestGASCharacterFromActorInfo())
	{
		if (TestGASCharacter->IsLocallyControlled() && !TestGASCharacter->bPressedJump) {
			TestGASCharacter->UnCrouch();
			TestGASCharacter->Jump();
		}
	}
}

void UTestGASGameplayAbility_Jump::CharacterJumpStop()
{
	if (ATestGASCharacterBase* TestGASCharacter = GetTestGASCharacterFromActorInfo())
	{
		if (TestGASCharacter->IsLocallyControlled() && TestGASCharacter->bPressedJump) {
			TestGASCharacter->StopJumping();
		}
	}
}


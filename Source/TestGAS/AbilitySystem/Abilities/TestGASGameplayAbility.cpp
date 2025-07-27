#include "TestGASGameplayAbility.h"
#include "TestGASAbilitySystemComponent.h"
#include "TestGASPlayerController.h"
#include "TestGASCharacterBase.h"


UTestGASGameplayAbility::UTestGASGameplayAbility(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/):Super(ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
}

UTestGASAbilitySystemComponent* UTestGASGameplayAbility::GetTestGASAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UTestGASAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}

ATestGASPlayerController* UTestGASGameplayAbility::GetTestGASPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ATestGASPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

AController* UTestGASGameplayAbility::GetControllerFromActorInfo() const
{

	if (CurrentActorInfo) {
		if (AController* PC = CurrentActorInfo->PlayerController.Get()) {
			return PC;
		}

		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();
		while (TestActor) {
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}

			if (APawn* Pawn = Cast<APawn>(TestActor)) {
				return Pawn->GetController();
			}

			TestActor = TestActor->GetOwner();
		}
	}

	return nullptr;

}

ATestGASCharacterBase* UTestGASGameplayAbility::GetTestGASCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ATestGASCharacterBase>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

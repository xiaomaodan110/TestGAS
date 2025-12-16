#include "AnimNotifyState_IgnoreInput.h"

#include "TestGASCharacter.h"
#include "TestGASComboComponent.h"

UAnimNotifyState_IgnoreInput::UAnimNotifyState_IgnoreInput()
{

}

void UAnimNotifyState_IgnoreInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if ((InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Client) && InCharacter->GetLocalRole() == ROLE_AutonomousProxy) || InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Standalone) || InCharacter->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			InCharacter->DisableInput(InCharacter->GetWorld()->GetFirstPlayerController());
		}
	}
}

void UAnimNotifyState_IgnoreInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UAnimNotifyState_IgnoreInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if ((InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Client) && InCharacter->GetLocalRole() == ROLE_AutonomousProxy) || InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Standalone) || InCharacter->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			InCharacter->EnableInput(InCharacter->GetWorld()->GetFirstPlayerController());
		}
	}
}

FString UAnimNotifyState_IgnoreInput::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

#include "AnimNotifyState_StopSpeed.h"

#include "TestGASCharacter.h"
#include "TestGASComboComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimNotifyState_StopSpeed::UAnimNotifyState_StopSpeed()
{

}

void UAnimNotifyState_StopSpeed::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		MaxWalkSpeed = InCharacter->GetCharacterMovement()->MaxWalkSpeed;
		MinAnalogWalkSpeed = InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed;
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
		InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed = 0.f;
	}
}

void UAnimNotifyState_StopSpeed::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UAnimNotifyState_StopSpeed::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
		InCharacter->GetCharacterMovement()->MinAnalogWalkSpeed = MinAnalogWalkSpeed;
	}
}

FString UAnimNotifyState_StopSpeed::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

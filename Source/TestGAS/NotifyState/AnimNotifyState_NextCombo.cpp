#include "AnimNotifyState_NextCombo.h"

#include "TestGASCharacter.h"
#include "TestGASComboComponent.h"

UAnimNotifyState_NextCombo::UAnimNotifyState_NextCombo()
{

}

void UAnimNotifyState_NextCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration,  EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && !MeshComp->GetOuter()->GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer)) {
		if (ATestGASCharacterBase* TestGASCharacterBase = Cast<ATestGASCharacterBase>(MeshComp->GetOuter()))
		{
			if (UTestGASComboComponent* ComboComponent = TestGASCharacterBase->GetTestGASComboComponent())
			{
				ComboComponent->ResetPressed();
			}
		}
	}
}

void UAnimNotifyState_NextCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UAnimNotifyState_NextCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && !MeshComp->GetOuter()->GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer)) {
		if (ATestGASCharacter* TestGASCharacter = Cast<ATestGASCharacter>(MeshComp->GetOuter()))
		{
			if (UTestGASComboComponent* ComboComponent = TestGASCharacter->GetTestGASComboComponent())
			{ 
				if (ComboComponent->IsStillPressed()) {
					TestGASCharacter->ComboMelee();
				}
			}
		}
	}
}

FString UAnimNotifyState_NextCombo::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

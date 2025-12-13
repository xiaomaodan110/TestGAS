#include "AnimNotify_ResetCombo.h"

#include "TestGASCharacterBase.h"
#include "TestGASComboComponent.h"

UAnimNotify_ResetCombo::UAnimNotify_ResetCombo()
{

}

void UAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ATestGASCharacterBase* TestGASCharacterBase = Cast<ATestGASCharacterBase>(MeshComp->GetOwner()))
	{
		if (UTestGASComboComponent* ComboComponent = TestGASCharacterBase->GetTestGASComboComponent())
		{
			ComboComponent->ResetComboIndex(); 
		}
	}
}

FString UAnimNotify_ResetCombo::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}


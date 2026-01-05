#include "UI_Base.h"

#include "TestGASCharacterBase.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "GameFramework/PlayerController.h"

UUI_Base::UUI_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UUI_Base::PlayWidgetAnim(const FString& InAnimName)
{
	if (UWidgetAnimation* WidgetAnim = GetNameWidgetAnimation(InAnimName))
	{
		PlayAnimation(WidgetAnim);
	}
}

UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& InWidgetName)
{
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass()))
	{
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;

		UWidgetAnimation** FoundAnimation = TArrayAnimations.FindByPredicate([&](const UWidgetAnimation* Anim) {
			return Anim && Anim->GetFName().ToString() == (InWidgetName + FString("_INST"));
			});

		return *FoundAnimation;
	}

	return nullptr;
}

ATestGASCharacterBase* UUI_Base::UI_GetTestGASCharacterBase() const
{
	if (GetWorld()) {
		if (APlayerController* InPlayerController = GetWorld()->GetFirstPlayerController<APlayerController>()) {
			if (ATestGASCharacterBase* InCharacter = InPlayerController->GetPawn<ATestGASCharacterBase>()) {
				return InCharacter;
			}
		}
	}

	return nullptr;
}

#include "TestGASPlayerController.h"
#include "TestGASCharacterBase.h"
#include "TestGASPlayerState.h"
#include "TestGASAbilitySystemComponent.h"
#include "TestGASHUD.h"

ATestGASPlayerController::ATestGASPlayerController(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer:Get()*/):Super(ObjectInitializer)
{

}



ATestGASPlayerState* ATestGASPlayerController::GetTestGASPlayerState() const
{
	return CastChecked<ATestGASPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UTestGASAbilitySystemComponent* ATestGASPlayerController::GetTestGASAbilitySystemComponent() const
{
	ATestGASCharacterBase* TestGASCharacter = Cast<ATestGASCharacterBase>(GetPawn());
	if (TestGASCharacter) {
		return TestGASCharacter->GetTestGASAbilitySystemComponent();
	}

	return nullptr;
}

ATestGASHUD* ATestGASPlayerController::GetTestGASHUD() const
{
	return CastChecked<ATestGASHUD>(GetHUD(), ECastCheckedType::NullAllowed);
}

void ATestGASPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused) {
	if (UTestGASAbilitySystemComponent* TestGASASC = GetTestGASAbilitySystemComponent()) {
		TestGASASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
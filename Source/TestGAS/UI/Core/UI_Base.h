#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Base.generated.h"

class ATestGASCharacterBase;
class UWidgetAnimation;

UCLASS()
class TESTGAS_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	UUI_Base(const FObjectInitializer& ObjectInitializer);
protected:
	void PlayWidgetAnim(const FString& InAnimName);

	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetName);

	ATestGASCharacterBase* UI_GetTestGASCharacterBase() const;
};
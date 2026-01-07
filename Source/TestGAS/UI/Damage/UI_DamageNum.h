#pragma once

#include "CoreMinimal.h"
#include "UI_Base.h"
#include "UI_DamageNum.generated.h"

class UTextBlock;

UCLASS()
class TESTGAS_API UUI_DamageNum : public UUI_Base
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NumText;

public:
	virtual void NativeConstruct();

	void UpdateNum(const FText& InText);
	void UpdateNumColor(const FLinearColor& InColor);

};
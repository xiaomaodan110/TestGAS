#include "TestGASNumberPopActor.h"

#include "Components/WidgetComponent.h"
#include "UI_DamageNum.h"

ATestGASDamageNumActor::ATestGASDamageNumActor()
{
	DamageNumRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DamageNumRootComponent"));
	RootComponent = DamageNumRootComponent;

	PrimaryActorTick.bCanEverTick = false;

	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	DamageWidgetComponent->SetupAttachment(RootComponent);
	DamageWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InitialLifeSpan = 4.0;
}

void ATestGASDamageNumActor::UpdateNum(const FText& InText)
{
	if (DamageWidgetComponent) {
		if (UUI_DamageNum* Damage = Cast<UUI_DamageNum>(DamageWidgetComponent->GetUserWidgetObject())) {
			Damage->UpdateNum(InText);
		}
	}
}

void ATestGASDamageNumActor::UpdateNumColor(const FLinearColor& InColor)
{
	if (DamageWidgetComponent) {
		if (UUI_DamageNum* Damage = Cast<UUI_DamageNum>(DamageWidgetComponent->GetUserWidgetObject())) {
			Damage->UpdateNumColor(InColor);
		}
	}
}


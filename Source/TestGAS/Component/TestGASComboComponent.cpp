#include "TestGASComboComponent.h"


UTestGASComboComponent::UTestGASComboComponent(const FObjectInitializer& object_initializer):Super(object_initializer)
{
	// close tick.
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UTestGASComboComponent::GetComboIndex()
{
	return ComboIndex;
}

UAnimMontage* UTestGASComboComponent::GetNextComboAnimMontage()
{
	LastPlayMontage = ComboMontages[ComboIndex];

	return ComboMontages[ComboIndex];
}


UAnimMontage* UTestGASComboComponent::GetLastComboAnimMontage()
{
	return LastPlayMontage;
}

void UTestGASComboComponent::UpdateComboIndex()
{
	ComboIndex = (ComboIndex + 1) % (ComboMaxIndex + 1);
}

void UTestGASComboComponent::ResetComboIndex()
{
	ComboIndex = 0;
}

void UTestGASComboComponent::SetPressed()
{
	bShortPress = true;
}

void UTestGASComboComponent::ResetPressed()
{
	bShortPress = false;
}

bool UTestGASComboComponent::IsStillPressed()
{
	return bShortPress;
}

void UTestGASComboComponent::BeginPlay()
{
	Super::BeginPlay();

	check(ComboMontages.Num() > 0);

	ComboMaxIndex = ComboMontages.Num() - 1;
}

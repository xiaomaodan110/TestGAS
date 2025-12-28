#include "TestGASAttributeSet.h"
#include "TestGASAbilitySystemComponent.h"

class UWorld;

UTestGASAttributeSet::UTestGASAttributeSet()
{

}

UWorld* UTestGASAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UTestGASAbilitySystemComponent* UTestGASAttributeSet::GetGASAbilitySystemComponent() const
{
	return Cast<UTestGASAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

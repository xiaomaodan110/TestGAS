#include "TestGASAbilitySystemComponent.h"

#include "TestGASGameplayAbility.h"

UTestGASAbilitySystemComponent::UTestGASAbilitySystemComponent(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
:Super(ObjectInitializer)
{
    InputPressedSpecHandles.Reset();
    InputReleasedSpecHandles.Reset();
    InputHeldSpecHandles.Reset();
}

void UTestGASAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
    if (InputTag.IsValid()) {
        for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items) {
            if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) {
                InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
                InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
            }
        }
    }
}

void UTestGASAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
    if (InputTag.IsValid()) {
        for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items) {
            if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) {
                InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
                InputHeldSpecHandles.Remove(AbilitySpec.Handle);
            }
        }
    }
}


void UTestGASAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
    static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
    AbilitiesToActivate.Reset();

    for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles) {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle)) {
            if (AbilitySpec->Ability){
                AbilitySpec->InputPressed = true;

                if (AbilitySpec->IsActive()) {
                    AbilitySpecInputPressed(*AbilitySpec);
                }
                else {
                    const UTestGASGameplayAbility* LyraAbilityCod = Cast<UTestGASGameplayAbility>(AbilitySpec->Ability);
                    AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
                }
            }
        }
    }

    for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate) {
        TryActivateAbility(AbilitySpecHandle);
    }

    // process all abilities that had their input released this frame.
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles) {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle)) {
            if (AbilitySpec->Ability) {
                AbilitySpec->InputPressed = false;

                if (AbilitySpec->IsActive()) {
                    AbilitySpecInputReleased(*AbilitySpec);
                }
            }
        }
    }

	// clear the cached ability handles.
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UTestGASAbilitySystemComponent::ClearAbilityInput()
{
    InputPressedSpecHandles.Reset();
    InputReleasedSpecHandles.Reset();
    InputHeldSpecHandles.Reset();
}

void UTestGASAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
    Super::AbilitySpecInputPressed(Spec);

    if (Spec.IsActive()) {
        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}

void UTestGASAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
    Super::AbilitySpecInputReleased(Spec);
	if (Spec.IsActive()) {
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}

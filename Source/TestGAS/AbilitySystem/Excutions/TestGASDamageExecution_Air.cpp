#include "TestGASDamageExecution_Air.h"

#include "TestGASCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"

struct FDamageAirStatics {
	FGameplayEffectAttributeCaptureDefinition BaseDamageAirDef;

	FDamageAirStatics() {
		BaseDamageAirDef = FGameplayEffectAttributeCaptureDefinition(UTestGASCharacterAttributeSet::GetDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
	}
};

static FDamageAirStatics& DamageAirStatics() {
	static FDamageAirStatics Statics;
	return Statics;
}


void UTestGASDamageExecution_Air::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

#if WITH_SERVER_CODE
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayEffectContextHandle& EffectContextHandle = Spec.GetEffectContext();

	AActor* EffectCauser = EffectContextHandle.GetEffectCauser();

	UAbilitySystemComponent* EffectASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectCauser);

	UAbilitySystemComponent* OriginalASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	float Defense = 0.f;

	if (const UTestGASCharacterAttributeSet* EffectArr = Cast<UTestGASCharacterAttributeSet>(EffectASC->GetAttributeSet(UTestGASCharacterAttributeSet::StaticClass()))) {
		Defense = EffectArr->GetDefense();
	}

	float Attack = 0.f;
	if (const UTestGASCharacterAttributeSet* OriginalArr = Cast<UTestGASCharacterAttributeSet>(OriginalASC->GetAttributeSet(UTestGASCharacterAttributeSet::StaticClass()))) {
		Attack = OriginalArr->GetAttack();
	}

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	float BaseAirDamage = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageAirStatics().BaseDamageAirDef, EvaluationParams, BaseAirDamage);
	
	const float BaseAirDamageDone = FMath::Max(0.0f, BaseAirDamage + Attack - Defense);


	if (BaseAirDamage > 0.0f)
	{
		FGameplayModifierEvaluatedData DamageModData;
		DamageModData.Attribute = UTestGASCharacterAttributeSet::GetDamageAttribute();
		DamageModData.ModifierOp = EGameplayModOp::Additive;
		DamageModData.Magnitude = BaseAirDamageDone;
		OutExecutionOutput.AddOutputModifier(DamageModData);
	}

#endif
}

UTestGASDamageExecution_Air::UTestGASDamageExecution_Air()
{
	RelevantAttributesToCapture.Add(DamageAirStatics().BaseDamageAirDef);
}

#include "TestGASDamageExecution.h"

#include "TestGASCharacterAttributeSet.h"

struct FDamageStatics {
	FGameplayEffectAttributeCaptureDefinition BaseDamageDef;

	FDamageStatics() {
		BaseDamageDef = FGameplayEffectAttributeCaptureDefinition(UTestGASCharacterAttributeSet::GetDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
	}
};

static FDamageStatics& DamageStatics() {
	static FDamageStatics Statics;
	return Statics;
}

UTestGASDamageExecution::UTestGASDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().BaseDamageDef);
}

void UTestGASDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

#if WITH_SERVER_CODE
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTags;
	EvaluationParams.TargetTags = TargetTags;

	float BaseDamage = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaseDamageDef, EvaluationParams, BaseDamage);


	const float DamageDone = FMath::Max(0.0f, BaseDamage);
	if (DamageDone > 0.0f)
	{
		FGameplayModifierEvaluatedData DamageModData;
		DamageModData.Attribute = UTestGASCharacterAttributeSet::GetDamageAttribute();
		DamageModData.ModifierOp = EGameplayModOp::Additive;
		DamageModData.Magnitude = DamageDone;
		OutExecutionOutput.AddOutputModifier(DamageModData);
	}

#endif
}

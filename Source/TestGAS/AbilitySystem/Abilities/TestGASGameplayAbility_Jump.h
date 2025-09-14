#include "TestGASGameplayAbility.h"

#include "TestGASGameplayAbility_Jump.generated.h"

class UObject;
struct FFrame;
struct FGameplayAbilityActorInfo;
struct FGameplayTagContainer;


UCLASS(Abstract)
class TESTGAS_API UTestGASGameplayAbility_Jump : public UTestGASGameplayAbility {
	GENERATED_BODY()

public:
	UTestGASGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayTagContainer* SourceTags /* = nullptr */, 
		const FGameplayTagContainer* TargetTags /* = nullptr */, 
		OUT FGameplayTagContainer* OptionalRelevantTags /* = nullptr */) const override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, 
		bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	void CharacterJumpStart();

	UFUNCTION(BlueprintCallable, Category = "TestGAS|Ability")
	void CharacterJumpStop();
};
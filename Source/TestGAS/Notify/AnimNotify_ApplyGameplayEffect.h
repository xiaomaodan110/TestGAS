#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayEffect.h"
#include "AnimNotify_ApplyGameplayEffect.generated.h"

class ATestGASHitBox_ApplyGameEffect;

UCLASS(meta = (DisplayName = "ApplyGameplayEffect"))
class TESTGAS_API UAnimNotify_ApplyGameplayEffect : public UAnimNotify {

	GENERATED_BODY()

public:
	UAnimNotify_ApplyGameplayEffect();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	TSubclassOf<ATestGASHitBox_ApplyGameEffect> HitObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	FVector RelativeOffsetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	FRotator RotationOffset;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	FName InSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	bool bBind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General Configuration")
	FVector BoxExtent;
};
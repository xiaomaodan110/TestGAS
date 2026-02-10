#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "TestGASHitBox_ApplyGameEffect.generated.h"


class ATestGASCharacterBase;
class UProjectileMovementComponent;

UENUM(BlueprintType)
enum class ETestGASHitCollisionType : uint8
{
	HITCOLLISIONTYPE_SHORT_RANGE_ATTACK UMETA(DisplayName = "Short range attack"), // 近战攻击
	HITCOLLISIONTYPE_DIRECT_LINE UMETA(DisplayName = "Direct Line"), // 无障碍直线攻击
	HITCOLLISIONTYPE_LINE UMETA(DisplayName = "Line"), // 非跟踪类型，类似手枪子弹
	HITCOLLISIONTYPE_TRACK_LINE  UMETA(DisplayName = "Track Line"), // 跟踪类型
	HITCOLLISIONTYPE_RANGE_LINE UMETA(DisplayName = "Range Line"), // 范围类型，丢手雷
	HITCOLLISIONTYPE_RANGE UMETA(DisplayName = "Range"), // 范围类型，类似自爆
	HITCOLLISIONTYPE_CHAIN   UMETA(DisplayName = "Chain"), // 链式攻击，持续伤害类型
};

UCLASS(BlueprintType, Blueprintable)
class TESTGAS_API ATestGASHitBox_ApplyGameEffect : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;
public:
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	ETestGASHitCollisionType HitCollisionType;

public:
	ATestGASHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void PreInitCollision(AActor* InMyInstigator);

	UFUNCTION()
	virtual void HandleDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetHitDamageRelativePosition(const FVector& InNewPosition);

	void SetBoxExtent(const FVector& InNewBoxExtent);

	void setGameplayEffect(TSubclassOf<UGameplayEffect>& InGE) {
		EffectClass = InGE;
	};

	bool IsExist(ATestGASCharacterBase* InNewTarget) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY()
	TArray<TWeakObjectPtr<ATestGASCharacterBase>> AttackedTarget;
};
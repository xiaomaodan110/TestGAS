#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"

#include "TestGASHitBox.generated.h"


class ATestGASCharacterBase;

UCLASS(BlueprintType, Blueprintable)
class TestGAS_API ATestGASHitBox : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitDamage;

public:
	ATestGASHitBox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// note UFUNCTION is must in this override function
	UFUNCTION()
	virtual void HandleDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetHitDamageRelativePosition(const FVector& InNewPosition);

	void SetBoxExtent(const FVector& InNewBoxExtent);

	void SetBuffs(const TArray<FGameplayTagContainer>& InBuffs) { BuffsTags = InBuffs; };

	bool IsExist(ATestGASCharacterBase* InNewTarget) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
		 
protected:
	UPROPERTY()
	TArray<FGameplayTagContainer> BuffsTags;

	UPROPERTY()
	TArray<TWeakObjectPtr<ATestGASCharacterBase>> AttackedTarget;
};
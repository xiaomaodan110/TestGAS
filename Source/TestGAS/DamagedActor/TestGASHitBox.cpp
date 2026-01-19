#include "TestGASHitBox.h"

#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "TestGASCharacterBase.h"
#include "Abilities/GameplayAbilityTypes.h"


ATestGASHitBox::ATestGASHitBox(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;


}

void ATestGASHitBox::HandleDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

UPrimitiveComponent* ATestGASHitBox::GetHitDamage()
{
	return nullptr;
}

void ATestGASHitBox::SetHitDamageRelativePosition(const FVector& InNewPosition)
{
}

void ATestGASHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
}

bool ATestGASHitBox::IsExist(ATestGASCharacterBase* InNewTarget) const
{
	return false;
}

void ATestGASHitBox::BeginPlay()
{
}

void ATestGASHitBox::Tick(float DeltaTime)
{
}

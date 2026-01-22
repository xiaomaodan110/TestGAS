#include "TestGASHitBox.h"

#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "TestGASCharacterBase.h"
#include "Abilities/GameplayAbilityTypes.h"


ATestGASHitBox::ATestGASHitBox(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);

	InitialLifeSpan = 4.f;
	bNetLoadOnClient = false;
	bReplicates = false;
}

void ATestGASHitBox::HandleDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

UPrimitiveComponent* ATestGASHitBox::GetHitDamage()
{
	return HitDamage;
}

void ATestGASHitBox::SetHitDamageRelativePosition(const FVector& InNewPosition)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage()) {
		InHitComponent->SetRelativeLocation(InNewPosition);
	}
}

void ATestGASHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

bool ATestGASHitBox::IsExist(ATestGASCharacterBase* InNewTarget) const
{

	for (auto& Tmp: AttackedTarget) {
		if (Tmp.IsValid()){
			if( Tmp == InNewTarget) {
				return true;
			}
		}
	}

	return false;
}

void ATestGASHitBox::BeginPlay()
{
}

void ATestGASHitBox::Tick(float DeltaTime)
{
}
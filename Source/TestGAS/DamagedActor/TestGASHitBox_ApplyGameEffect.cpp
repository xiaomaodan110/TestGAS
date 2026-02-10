#include "TestGASHitBox_ApplyGameEffect.h"

#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "TestGASCharacterBase.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATestGASHitBox_ApplyGameEffect::ATestGASHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) 
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);

	InitialLifeSpan = 4.f;
	bNetLoadOnClient = true; 
	bReplicates = true;  // sync effects
	SetReplicatingMovement(true); // sync movement

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->SetUpdatedComponent(RootComponent);
	ProjectileMovement->SetIsReplicated(true);

	// Ä¬ÈÏ½ü³Ì¹¥»÷
	HitCollisionType = ETestGASHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK;

}

void ATestGASHitBox_ApplyGameEffect::PreInitCollision(AActor* InMyInstigator)
{
	if (!InMyInstigator) {
		return;
	}

	FVector ShootDirection = InMyInstigator->GetActorRotation().Vector();

	switch (HitCollisionType)
	{	
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK:

		ProjectileMovement->MaxSpeed = 0.f;
		ProjectileMovement->InitialSpeed = 0.f;
		ProjectileMovement->ProjectileGravityScale = 0.f;
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_DIRECT_LINE:
		RootComponent->SetWorldRotation(FRotator::ZeroRotator);
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_LINE:
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_TRACK_LINE:
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_RANGE_LINE:
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_RANGE:
		break;
	case ETestGASHitCollisionType::HITCOLLISIONTYPE_CHAIN:
		break;
	default:
		break;
	}
}

void ATestGASHitBox_ApplyGameEffect::HandleDamage(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator()) {

		if (ATestGASCharacterBase* InTarget = Cast<ATestGASCharacterBase>(OtherActor)) {
			if (!InTarget->IsNetMode(ENetMode::NM_Client)) {

				if (IsExist(InTarget)) {
					return;
				}

				if (UAbilitySystemComponent* InAbilitySystemComponent = InTarget->GetAbilitySystemComponent()) {

					FGameplayEffectContextHandle EffectContextHandle = InAbilitySystemComponent->MakeEffectContext();

					EffectContextHandle.AddInstigator(GetInstigator(), this);
					EffectContextHandle.AddSourceObject(InTarget);


					// create GE
					FGameplayEffectSpecHandle EffectSpecHandle = InAbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContextHandle);
					if (EffectSpecHandle.IsValid()) {
						InAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), InAbilitySystemComponent);
					}

					AttackedTarget.AddUnique(InTarget); 
				}

			}

		}

	}
}

UPrimitiveComponent* ATestGASHitBox_ApplyGameEffect::GetHitDamage()
{
	return HitDamage;
}

void ATestGASHitBox_ApplyGameEffect::SetHitDamageRelativePosition(const FVector& InNewPosition)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage()) {
		InHitComponent->SetRelativeLocation(InNewPosition);
	}
}

void ATestGASHitBox_ApplyGameEffect::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

bool ATestGASHitBox_ApplyGameEffect::IsExist(ATestGASCharacterBase* InNewTarget) const
{
	for (auto& Tmp : AttackedTarget) {
		if (Tmp.IsValid()) {
			if (Tmp == InNewTarget) {
				return true;
			}
		}
	}

	return false;
}

void ATestGASHitBox_ApplyGameEffect::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* InHitComponent = GetHitDamage()) {
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &ATestGASHitBox_ApplyGameEffect::HandleDamage);
	}
}

void ATestGASHitBox_ApplyGameEffect::Tick(float DeltaTime)
{

}


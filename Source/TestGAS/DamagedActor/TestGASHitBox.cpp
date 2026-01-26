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
	if (GetInstigator() != OtherActor) {
		if (ATestGASCharacterBase* InPawn = Cast<ATestGASCharacterBase>(GetInstigator())) {

			if (ATestGASCharacterBase* InTarget = Cast<ATestGASCharacterBase>(OtherActor)) {

				if (!InPawn->IsNetMode(ENetMode::NM_Client)) {
					FGameplayEventData EventData;
					EventData.Instigator = GetInstigator();
					EventData.Target = InTarget;

					if (IsExist(InTarget)) {
						return;
					}

					if (!BuffsTags.IsEmpty()) {
						for (auto& Tmp : BuffsTags) {
							UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), Tmp.Last(), EventData);
						}
					}
				
					AttackedTarget.AddUnique(InTarget);
				}
			}
		}
	}
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
	Super::BeginPlay();
	if (UPrimitiveComponent* InHitComponent = GetHitDamage()) {
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &ATestGASHitBox::HandleDamage);
	}
}

void ATestGASHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#include "AnimNotify_ApplyGameplayEffect.h"

#include "TestGASHitBox_ApplyGameEffect.h"
#include "TestGASCharacterBase.h"

UAnimNotify_ApplyGameplayEffect::UAnimNotify_ApplyGameplayEffect()
	:Super()
{
	HitObjectClass = ATestGASHitBox_ApplyGameEffect::StaticClass();
	BoxExtent = FVector(32.f);
	LifeTime = 4.0f;
	InSocketName = TEXT("OpenFire");
}

void UAnimNotify_ApplyGameplayEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter())) {
		if (!(InCharacter->GetWorld()->GetNetMode() == ENetMode::NM_Client)) {
			FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
			FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

			ATestGASCharacterBase* CheckCharacter = Cast<ATestGASCharacterBase>(InCharacter);

			if (!CheckCharacter) {
				ComponentRotation += FRotator(0, 90, 0);
			}

			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);
			FString VForward = ComponentLocation.ToString();

			// GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT(",%s"), *VForward));

			if (ATestGASHitBox_ApplyGameEffect* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ATestGASHitBox_ApplyGameEffect>(
				HitObjectClass, Transform, NULL, Cast<APawn>(InCharacter), ESpawnActorCollisionHandlingMethod::AlwaysSpawn)) {

				HitCollision->PreInitCollision(InCharacter);

				HitCollision->setGameplayEffect(EffectClass);
				HitCollision->SetBoxExtent(BoxExtent);

				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);

				HitCollision->SetLifeSpan(LifeTime);

				HitCollision->FinishSpawning(Transform);

				if (bBind) {
					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
				}
			}
		}
	}
}

FString UAnimNotify_ApplyGameplayEffect::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}


#include "AnimNotify_Attack.h"

#include "TestGASHitBox.h"

UAnimNotify_Attack::UAnimNotify_Attack()
{
	HitObjectClass = ATestGASHitBox::StaticClass();
	BoxExtent = FVector(32.f);
	LifeTime = 4.0f;
	InSocketName = TEXT("OpenFire");
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		if (!InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Client)) {
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			if (ATestGASHitBox* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ATestGASHitBox>(
			HitObjectClass,Transform, NULL, Cast<APawn>(InCharacter), ESpawnActorCollisionHandlingMethod::AlwaysSpawn)) {
				HitCollision->SetBuffs(BuffTags);
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
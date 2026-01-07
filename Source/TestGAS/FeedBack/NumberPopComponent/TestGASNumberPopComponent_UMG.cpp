#include "TestGASNumberPopComponent_UMG.h"
#include "TestGASNumberPopActor.h"

UTestGASNumberPopComponent_UMG::UTestGASNumberPopComponent_UMG(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UTestGASNumberPopComponent_UMG::AddNumberPop(const FTestGASNumberPopRequest& NewRequest)
{
	if (APlayerController* PC = GetOwner<APlayerController>()) {
		if (!PC->IsLocalController()) {
			return;
		}
	}

	// Determine the position
	FTransform CameraTransform;
	FVector NumberLocation(NewRequest.WorldLocation);
	if (APlayerController* PC = GetController<APlayerController>())
	{
		if (APlayerCameraManager* PlayerCameraManager = PC->PlayerCameraManager)
		{
			CameraTransform = FTransform(PlayerCameraManager->GetCameraRotation(), PlayerCameraManager->GetCameraLocation());

			FVector LocationOffset(ForceInitToZero);

			const float RandomMagnitude = 5.0f; //@TODO: Make this style driven
			LocationOffset += FMath::RandPointInBox(FBox(FVector(-RandomMagnitude), FVector(RandomMagnitude)));

			NumberLocation += LocationOffset;
		}
	}

	if (UWorld* LocalWorld = GetWorld()) {
		ATestGASDamageNumActor* PopActor = LocalWorld->SpawnActor<ATestGASDamageNumActor>(NumPopActorClass, NewRequest.WorldLocation, FRotator::ZeroRotator);

		PopActor->UpdateNum(FText::FromString(FString::FromInt(NewRequest.NumberToDisplay)));
		PopActor->UpdateNumColor(NewRequest.ColorToDisplay);
	}
}

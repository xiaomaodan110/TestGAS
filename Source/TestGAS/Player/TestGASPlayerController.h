#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestGASPlayerController.generated.h"

UCLASS(Config = Game, Meta = (ShortToolTip = "The base player controller class used by this project."))
class ATestGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATestGASPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};




#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TestGASPlayerController.generated.h"


class ATestGASPlayerState;
class UTestGASAbilitySystemComponent;
class ATestGASHUD;

UCLASS(Config = Game, Meta = (ShortToolTip = "The base player controller class used by this project."))
class ATestGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATestGASPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "TestGAS|PlayerController")
	ATestGASPlayerState* GetTestGASPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|PlayerController")
	UTestGASAbilitySystemComponent* GetTestGASAbilitySystemComponent() const;

	//UFUNCTION(BlueprintCallable, Category = "TestGAS|PlayerController")
	//UTestGASNumberPopComponent* GetTestGASNumberPopComponent() const;

	UFUNCTION(BlueprintCallable, Category = "TestGAS|PlayerController")
	ATestGASHUD* GetTestGASHUD() const;


	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};




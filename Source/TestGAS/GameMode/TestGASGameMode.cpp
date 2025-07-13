// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestGASGameMode.h"

#include "TestGASCharacter.h"
#include "TestGASGameState.h"

#include "TestGASPlayerController.h"
#include "TestGASPlayerState.h"
#include "TestGASHUD.h"

#include "UObject/ConstructorHelpers.h"

ATestGASGameMode::ATestGASGameMode()
{
	GameStateClass = ATestGASGameState::StaticClass();

	PlayerControllerClass = ATestGASPlayerController::StaticClass();
	PlayerStateClass = ATestGASPlayerState::StaticClass();
	DefaultPawnClass = ATestGASCharacter::StaticClass();

	HUDClass = ATestGASHUD::StaticClass();
}

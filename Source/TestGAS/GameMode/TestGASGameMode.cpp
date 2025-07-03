// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestGASGameMode.h"
#include "TestGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestGASGameMode::ATestGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonResource/ThirdPerson/Blueprints/BP_TestGASCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

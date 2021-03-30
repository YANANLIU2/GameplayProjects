// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_D_Fight_GameGameMode.h"
#include "A_D_Fight_GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AA_D_Fight_GameGameMode::AA_D_Fight_GameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

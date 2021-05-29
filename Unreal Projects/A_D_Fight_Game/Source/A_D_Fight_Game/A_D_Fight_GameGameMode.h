// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "A_D_Fight_GameGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FGameModeLoggerSignature, FString);
UCLASS(minimalapi)
class AA_D_Fight_GameGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	// Gameplay loops
	enum class GameplayLoop
	{
		kPrimaryLoop, // Race to conquer as many arenas in a lap or 2.
		kSecondaryLoop // Complete challenges to conquer the arena.
	};

public:
	AA_D_Fight_GameGameMode();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) sealed;

	void BeginPlay() sealed;

	/** Return GameSession class to use for this game  */
	TSubclassOf<AGameSession> GetGameSessionClass() const sealed;

private:
	FGameModeLoggerSignature LogWritter_OnLogging;

	void PowerUpActivatedLogging();
};




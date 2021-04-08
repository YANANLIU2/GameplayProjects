// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "A_D_Fight_GameGameMode.generated.h"

DECLARE_DELEGATE_OneParam(FLogWritterSignature, FString);
UCLASS(minimalapi)
class AA_D_Fight_GameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AA_D_Fight_GameGameMode();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) sealed;

	void BeginPlay() sealed;

	/** Return GameSession class to use for this game  */
	TSubclassOf<AGameSession> GetGameSessionClass() const sealed;

private:
	FLogWritterSignature LogWritter_OnLogging;
};




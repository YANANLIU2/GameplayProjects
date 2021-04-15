// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_D_Fight_GameGameMode.h"
#include "A_D_Fight_GameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/OnlineEngineInterface.h"
#include "A_D_Fight_GameSession.h"
#include "Utilities/LogWritter.h"
#include "GamePlay/Events/PowerUpBroadcaster.h"

AA_D_Fight_GameGameMode::AA_D_Fight_GameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameSessionClass = A_D_Fight_GameSession::StaticClass();
}

void AA_D_Fight_GameGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	UWorld* World = GetWorld();

	// Save Options for future use
	OptionsString = Options;

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save game sessions into a map
	GameSession = World->SpawnActor<A_D_Fight_GameSession>(GetGameSessionClass(), SpawnInfo);
	GameSession->InitOptions(Options);

	FGameModeEvents::GameModeInitializedEvent.Broadcast(this);

	if (GetNetMode() != NM_Standalone)
	{
		// Attempt to login, returning true means an async login is in flight
		if (!UOnlineEngineInterface::Get()->DoesSessionExist(World, GameSession->SessionName) &&
			!GameSession->ProcessAutoLogin())
		{
			GameSession->RegisterServer();
		}
	}

	// Binding the log writter
	LogWritter_OnLogging.BindRaw(&LogWritter::get_instance(), &LogWritter::LogOnConsole);

	// Binding the power up broadcaster
	PowerUpBroadcaster::GetInstance().OnPowerUpActivated().AddUObject(this, &AA_D_Fight_GameGameMode::PowerUpActivatedLogging);
}

void AA_D_Fight_GameGameMode::BeginPlay()
{
	Super::BeginPlay();
	LogWritter_OnLogging.Execute(FString("BeginPlay"));
}

TSubclassOf<AGameSession> AA_D_Fight_GameGameMode::GetGameSessionClass() const
{
	if (UClass* Class = GameSessionClass.Get())
	{
		return Class;
	}

	return A_D_Fight_GameSession::StaticClass();
}

void AA_D_Fight_GameGameMode::PowerUpActivatedLogging()
{
	LogWritter_OnLogging.Execute(FString("Power up is refreshed"));
}

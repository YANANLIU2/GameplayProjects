// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class A_D_FIGHT_GAME_API AEnemyBase : public APawn
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle;

	// Is the enemy alive or not
	bool IsAlive;
	float HealthPoints;
	float MaxHealthPoints;

public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisualMesh;

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

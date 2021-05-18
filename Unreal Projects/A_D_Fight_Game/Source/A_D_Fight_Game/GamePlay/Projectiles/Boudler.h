// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Boudler.generated.h"

UCLASS()
class A_D_FIGHT_GAME_API ABoudler : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;
public:	
	// Sets default values for this actor's properties
	ABoudler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);
};

// Fill out your copyright notice in the Description page of Project Settings.
#include "PowerUpBase.h"
#include "A_D_Fight_Game/GamePlay/Events/PowerUpBroadcaster.h"

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set static mesh
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	bIsCollected = false;

	VisualMesh->OnComponentBeginOverlap.AddDynamic(this, &APowerUpBase::OnOverlapBegin);
}

void APowerUpBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsCollected)
	{
		bIsCollected = true;

		VisualMesh->SetVisibility(false);

		// Set timer
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APowerUpBase::Activate, TimerInterval, false);
	}
}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
	PowerUpBroadcaster::GetInstance().BroadPowerUpActivated();
}

void APowerUpBase::Activate()
{
	VisualMesh->SetVisibility(true);

	PowerUpBroadcaster::GetInstance().BroadPowerUpActivated();

	bIsCollected = false;
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Make our power up simultaneously rotate while also floating up and down
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * RotationSpeed;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void APowerUpBase::PostInitProperties()
{
	Super::PostInitProperties();
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "A_D_Fight_GameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utilities/LogWritter.h"

//////////////////////////////////////////////////////////////////////////
// AA_D_Fight_GameCharacter

AA_D_Fight_GameCharacter::AA_D_Fight_GameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Binding the log writter
	LogWritter_OnLogging.BindRaw(&LogWritter::get_instance(), &LogWritter::LogOnConsole);

	// Test speed
	RunMaxSpeed = 1200;
	WalkMaxSpeed = 600;

	// Set Boulder Spawn Offset to spawn projectiles slightly in front of the player.
	BoulderSpawnOffset.Set(100.0f, 0.0f, 0.0f);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AA_D_Fight_GameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AA_D_Fight_GameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AA_D_Fight_GameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AA_D_Fight_GameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AA_D_Fight_GameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AA_D_Fight_GameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AA_D_Fight_GameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AA_D_Fight_GameCharacter::OnResetVR);

	// Custom actions 
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AA_D_Fight_GameCharacter::RunStarted);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AA_D_Fight_GameCharacter::RunEnded);

	PlayerInputComponent->BindAction("Fly", IE_Pressed, this, &AA_D_Fight_GameCharacter::FlyStarted);
	PlayerInputComponent->BindAction("Fly", IE_Released, this, &AA_D_Fight_GameCharacter::FlyEnded);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AA_D_Fight_GameCharacter::Attack);
	PlayerInputComponent->BindAction("Defend", IE_Pressed, this, &AA_D_Fight_GameCharacter::Defend);
	PlayerInputComponent->BindAction("Counter", IE_Pressed, this, &AA_D_Fight_GameCharacter::Counter);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AA_D_Fight_GameCharacter::Block);
	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &AA_D_Fight_GameCharacter::Evade);
}

void AA_D_Fight_GameCharacter::OnResetVR()
{
	// If A_D_Fight_Game is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in A_D_Fight_Game.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AA_D_Fight_GameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AA_D_Fight_GameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AA_D_Fight_GameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AA_D_Fight_GameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AA_D_Fight_GameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AA_D_Fight_GameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AA_D_Fight_GameCharacter::FireABoulder()
{
	// Transform BoulderSpawnOffset from relative to the boss space to world space.
	FVector BoudlerLocation = this->GetActorLocation() + FTransform(this->GetActorRotation()).TransformVector(BoulderSpawnOffset);

	// Skew the aim to be slightly upwards.
	FRotator BoudlerRotation = this->GetActorRotation();
	BoudlerRotation.Pitch += 10.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn the projectile at the muzzle.
		ABoudler* Boudler = World->SpawnActor<ABoudler>(BoulderProjectileClass, BoudlerLocation, BoudlerRotation, SpawnParams);
		if (Boudler)
		{
			// Set the projectile's initial trajectory.
			FVector LaunchDirection = BoudlerRotation.Vector();
			Boudler->FireInDirection(LaunchDirection);
		}
	}
}

void AA_D_Fight_GameCharacter::Attack()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Attack"));
}

void AA_D_Fight_GameCharacter::Defend()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Defend"));
}

void AA_D_Fight_GameCharacter::Counter()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Counter"));
}

void AA_D_Fight_GameCharacter::Block()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Block"));
}

void AA_D_Fight_GameCharacter::Evade()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Evade"));
}

void AA_D_Fight_GameCharacter::RunStarted()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Run Started"));
	GetCharacterMovement()->MaxWalkSpeed = RunMaxSpeed;
}

void AA_D_Fight_GameCharacter::RunEnded()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Run Ended"));
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;
}

void AA_D_Fight_GameCharacter::FlyStarted()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Fly Started"));
}

void AA_D_Fight_GameCharacter::FlyEnded()
{
	LogWritter_OnLogging.Execute(FString("GameCharacter: Fly Ended"));
}



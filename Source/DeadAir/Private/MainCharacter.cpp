// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first-person camera component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FirstPersonCameraComponent != nullptr);

	// Create a first person mesh component for the owning player.
	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FirstPersonMeshComponent != nullptr);

	// Attach the first-person mesh to the third-person mesh
	FirstPersonMeshComponent->SetupAttachment(GetMesh());
	FirstPersonMeshComponent->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	// Set the first person mesh to not collide with other objects
	FirstPersonMeshComponent->SetCollisionProfileName(FName("NoCollision"));

	// Treat the 3rd-person mesh as a regular world object
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	// Attach the camera component to the first-person Skeletal Mesh.
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMeshComponent, FName("head"));

	// Position the camera slightly above the eyes and rotate it to behind the player's head
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0.0f, 90.0f, -90.0f));

	// Enable the pawn to control camera rotation.
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Enable first-person rendering and set default FOV and scale values
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = FirstPersonFieldOfView;
	FirstPersonCameraComponent->FirstPersonScale = FirstPersonScale;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Set the animations on the first person mesh.
	FirstPersonMeshComponent->SetAnimInstanceClass(FirstPersonDefaultAnim->GeneratedClass);

	// Set the animations on the third-person mesh.
	GetMesh()->SetAnimInstanceClass(FirstPersonDefaultAnim->GeneratedClass);

	// Only the owning player sees the first-person mesh
	FirstPersonMeshComponent->SetOnlyOwnerSee(true);

	// Hide the 3rd-person mesh from the owning player
	GetMesh()->SetOwnerNoSee(true);
	// Make the 3rd-person mesh cast a shadow
	GetMesh()->CastShadow = true;
	GetMesh()->bCastHiddenShadow = true;

	// Get the player controller that is possessing this character
	APlayerController *PlayerController = GetController<APlayerController>();

	// Get the enhanced input local player subsystem and add a new input mapping context to it
	if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(FirstPersonContext, 0);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using AdventureCharacter."));
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// Bind Jump Actions
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
	}
}

void AMainCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller)
	{
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementValue.X);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue.Y);
	}
}

void AMainCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

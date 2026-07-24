// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	check(WeaponMesh != nullptr);
	WeaponMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	RootComponent = WeaponMesh;
	MuzzleFlashMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuzzleFlashMesh"));
	check(MuzzleFlashMesh != nullptr);
	MuzzleFlashMesh->SetVisibility(false);
	MuzzleFlashMesh->SetRelativeScale3D(FVector(1));
	MuzzleFlashMesh->SetupAttachment(WeaponMesh, FName("MuzzleSocket"));
	MuzzleFlashMesh->SetCollisionProfileName(FName("NoCollision"));
	MuzzleFlashMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->SetOnlyOwnerSee(true);
	MuzzleFlashMesh->SetOnlyOwnerSee(true);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Fire(AMainCharacter *Shooter)
{
	if (Shooter == nullptr)
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Fire!!!!"));
	UAnimInstance *AnimInstance = Shooter->FirstPersonMeshComponent->GetAnimInstance();
	if (AnimInstance && ArmFireMontage)
	{
		AnimInstance->Montage_Play(ArmFireMontage);
	}
	UAnimInstance *WeaponAnimInstance = WeaponMesh->GetAnimInstance();

	if (WeaponAnimInstance && WeaponFireMontage)
	{
		WeaponAnimInstance->Montage_Play(WeaponFireMontage);
	}

	MuzzleFlashMesh->SetVisibility(true);
	GetWorldTimerManager().SetTimer(
		MuzzleFlashTimerHandle,
		this,
		&AWeapon::HideMuzzleFlash,
		0.05f,
		false);
	UGameplayStatics::PlaySound2D(this, FireSound);
}

void AWeapon::HideMuzzleFlash()
{
	MuzzleFlashMesh->SetVisibility(false);
}

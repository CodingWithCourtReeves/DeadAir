// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class AMainCharacter;

UCLASS()
class DEADAIR_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> MuzzleFlashMesh;

	UPROPERTY(EditAnywhere, Category = Audio)
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<UAnimMontage> WeaponFireMontage;

	// Handles fire input
	UFUNCTION()
	void Fire(AMainCharacter *Shooter);

	FTimerHandle MuzzleFlashTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void HideMuzzleFlash();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

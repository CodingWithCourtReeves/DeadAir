// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEADAIR_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float MaxArmor = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	float CurrentArmor = 0.0f;

	void ApplyDamage(float Amount);
	void Heal(float Amount);
	void AddArmor(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

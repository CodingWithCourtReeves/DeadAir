// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentArmor = MaxArmor;
}

void UHealthComponent::ApplyDamage(float Amount)
{
	if (CurrentArmor <= 0 && CurrentHealth <= 0)
	{
		return;
	}

	if (CurrentArmor > 0)
	{
		CurrentArmor -= Amount;

		if (CurrentArmor < 0)
		{
			CurrentHealth -= FMath::Abs(CurrentArmor);
			CurrentArmor = 0;
		}
	}
	else
	{

		CurrentHealth -= Amount;
	}

	CurrentHealth = CurrentHealth < 0 ? 0 : CurrentHealth;
}

void UHealthComponent::Heal(float Amount)
{
	CurrentHealth = FMath::Min(CurrentHealth + Amount, MaxHealth);
}

void UHealthComponent::AddArmor(float Amount)
{
	CurrentArmor = FMath::Min(CurrentArmor + Amount, MaxArmor);
}

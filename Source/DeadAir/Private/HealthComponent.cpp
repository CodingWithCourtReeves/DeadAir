// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentArmor = MaxArmor;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

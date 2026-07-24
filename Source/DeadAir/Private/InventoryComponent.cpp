// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddWeapon(AWeapon *Weapon)
{
	if (Weapons.Contains(Weapon))
	{
		// TODO: Add ammo
		return;
	}

	Weapons.Add(Weapon);

	if (CurrentWeapon == nullptr)
	{
		CurrentWeapon = Weapon;
	}
}

void UInventoryComponent::SwitchToIndex(int Index)
{
	if (!Weapons.IsValidIndex(Index))
	{
		return;
	}

	CurrentWeapon = Weapons[Index];
}

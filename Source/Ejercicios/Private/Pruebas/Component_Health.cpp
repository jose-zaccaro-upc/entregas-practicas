// Fill out your copyright notice in the Description page of Project Settings.


#include "Pruebas/Component_Health.h"

#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Pruebas/Personalized_Character.h"


// Sets default values for this component's properties
UComponent_Health::UComponent_Health()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	Strength = 1;
	MaxEnergy = 100;
	Energy = MaxEnergy;
	
	// ...
}


// Called when the game starts
void UComponent_Health::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UComponent_Health::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Implementación de nuestro método
void UComponent_Health::SayHello()
{
	GEngine->AddOnScreenDebugMessage(-1,1.f,FColor::Green, TEXT("Hola perri"));
}

void UComponent_Health::AddHealth(int Heal)
{
	CurrentHealth += Heal;
}

int UComponent_Health::MinusHealth(int Heal)
{
	const int newHealth = FMath::Clamp(CurrentHealth - Heal, 0, MaxHealth);;
	
	CurrentHealth = newHealth;

	if (CurrentHealth == 0)
	{
		OnPlayerDeath.Broadcast();
	}
	return CurrentHealth;
}


void UComponent_Health::SetMaxHealth(int Quantity)
{
	MaxHealth = Quantity;
}

void UComponent_Health::SetCurrentHealth(int Quantity)
{
	CurrentHealth = Quantity;
}

void UComponent_Health::SetStrength(int Quantity)
{
	Strength = Quantity;
}

void UComponent_Health::SetEnergy(int Quantity)
{
	Energy = Quantity;
}
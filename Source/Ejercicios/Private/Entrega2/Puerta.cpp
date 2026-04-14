// Fill out your copyright notice in the Description page of Project Settings.


#include "Entrega2/Puerta.h"

#include "Components/BoxComponent.h"


// Sets default values
APuerta::APuerta()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APuerta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuerta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuerta::Abrir()
{
	Destroy();
}


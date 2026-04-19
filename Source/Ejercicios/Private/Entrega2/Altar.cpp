// Fill out your copyright notice in the Description page of Project Settings.


#include "Entrega2/Altar.h"

#include "Components/SphereComponent.h"


// Sets default values
AAltar::AAltar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void AAltar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	OverlapActor = OtherActor;
	AltarOverlap.Broadcast(true);
}

void AAltar::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	OverlapActor = nullptr;
	AltarOverlap.Broadcast(false);
}

void AAltar::ActivateAltar()
{
	active = true;
	OnAltarActivated.Broadcast();
	GEngine->AddOnScreenDebugMessage(1,2.5f,FColor::Blue, TEXT("Altar ACTIVADO"));
	this->Destroy();
}

// Called when the game starts or when spawned
void AAltar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAltar::Interact_Implementation(AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(1,2.5f, FColor::Blue, TEXT("Activando Altar"));
	
	GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AAltar::ActivateAltar,
			2.5f,
			false
	);
	// GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Green,FString::Printf(TEXT("Interacted")));
}


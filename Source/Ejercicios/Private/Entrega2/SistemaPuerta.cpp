// Fill out your copyright notice in the Description page of Project Settings.


#include "Entrega2/SistemaPuerta.h"

#include "Components/BoxComponent.h"
#include "Entrega2/Altar.h"
#include "Entrega2/Puerta.h"


// Sets default values
ASistemaPuerta::ASistemaPuerta()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASistemaPuerta::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateLambda([this]() {
			GEngine->AddOnScreenDebugMessage(
				2,
				1.f,
				FColor::Red,
				FString::Printf(
					TEXT("Altares necesarios %i altares obtenidos %i"),
					Altares.Num(),
					AltaresObtenidos
				)
			);
		}),
		1.0f,
		true
	);
	
	for (AAltar* Altar : Altares)
	{
		Altar->OnAltarActivated.AddDynamic(this, &ASistemaPuerta::AbrirPuerta);
	} 

}

// Called every frame
void ASistemaPuerta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASistemaPuerta::AbrirPuerta()
{
	AltaresObtenidos++;
	if (AltaresObtenidos >= Altares.Num())
	{
		// Activar puerta / Destruir
		Puerta->Abrir();
	}
}


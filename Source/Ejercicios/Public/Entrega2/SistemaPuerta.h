// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SistemaPuerta.generated.h"

class UBoxComponent;
class AAltar;
class APuerta;

UCLASS()
class EJERCICIOS_API ASistemaPuerta : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASistemaPuerta();
	FTimerHandle TimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Members")
	TArray<AAltar*> Altares;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Members")
	APuerta* Puerta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Members")
	int AltaresObtenidos;
	
	UFUNCTION(BlueprintCallable)
	void AbrirPuerta();
	 
};

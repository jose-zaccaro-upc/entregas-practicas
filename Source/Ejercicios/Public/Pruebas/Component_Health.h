// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_Health.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EJERCICIOS_API UComponent_Health : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UComponent_Health();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --- PROPIEDADES ---
	// EditAnywhere: Lo ves en el panel de detalles.
	// BlueprintReadWrite: Podés usarlo en Blueprints.
	// Category: Para organizar tus variables en el editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CurrentStats")
	int CurrentHealth;
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	int Strength;
	UPROPERTY(EditAnywhere, Category = "CurrentStats")
	int Energy;
	UPROPERTY(EditAnywhere, Category = "CurrentStats")
	int MaxEnergy;
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SayHello();
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddHealth(int Heal);
	UFUNCTION(BlueprintCallable, Category = "Action")
	int MinusHealth(int Heal);
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPlayerDeathSignature OnPlayerDeath;
private:
	// --- MÉTODOS ---
	// BlueprintCallable: Permite llamar a esta función desde un Blueprint.
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetMaxHealth(int Quantity);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetCurrentHealth(int Quantity);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetStrength(int Quantity);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void SetEnergy(int Quantity);
	

	
};

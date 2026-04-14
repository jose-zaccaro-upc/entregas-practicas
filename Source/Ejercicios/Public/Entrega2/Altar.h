// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.h"
#include "GameFramework/Actor.h"
#include "Altar.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAltarActivatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAltarOverlapSignature, bool, overlaping);

UCLASS()
class EJERCICIOS_API AAltar : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAltar();
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAltarActivatedSignature OnAltarActivated;
	
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnAltarOverlapSignature AltarOverlap;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	TObjectPtr<AActor> OverlapActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool active = false;
	
	UPROPERTY()
	FTimerHandle TimerHandle;
	
	UFUNCTION(BlueprintCallable)
	void ActivateAltar();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void Interact_Implementation(AActor* Actor) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};

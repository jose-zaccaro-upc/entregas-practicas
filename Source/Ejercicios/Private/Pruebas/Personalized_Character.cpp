// Fill out your copyright notice in the Description page of Project Settings.


#include "Pruebas/Personalized_Character.h"
#include "Pruebas/Component_Health.h"
#include "EjerciciosCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Ejercicios.h"
#include "Entrega2/Altar.h"
#include "Entrega2/InteractInterface.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
APersonalized_Character::APersonalized_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	HealthComponent = CreateDefaultSubobject<UComponent_Health>(TEXT("HealthSystem"));
	HealthComponent->OnPlayerDeath.AddDynamic(this, &APersonalized_Character::DeathEvent);
	
}

// Called when the game starts or when spawned
void APersonalized_Character::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,          // El handle (ID del timer)
		this,                       // El objeto que tiene la función
		&APersonalized_Character::ShowHealth, // Referencia a la función
		1.f,                       // Tiempo de delay (float)
		true                       // ¿Debe repetirse (loop)?
	);
}

// Called every frame
void APersonalized_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APersonalized_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APersonalized_Character::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APersonalized_Character::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APersonalized_Character::Look);
		
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APersonalized_Character::Interact);
	}
	else
	{
		UE_LOG(LogEjercicios, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APersonalized_Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void APersonalized_Character::Interact(const FInputActionValue& Value)
{
	// input is a bool
	DoInteract();
}

void APersonalized_Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APersonalized_Character::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	OnMakeDamage_Implementation(20, OtherActor);
	OverlapActor = OtherActor;
}

void APersonalized_Character::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	OverlapActor = nullptr;
}

void APersonalized_Character::ShowHealth()
{
	GEngine->AddOnScreenDebugMessage(
	-1,
	1.f,
	FColor::Green,
FString::Printf(TEXT("Vida: %i"), HealthComponent->CurrentHealth));
}

void APersonalized_Character::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APersonalized_Character::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APersonalized_Character::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void APersonalized_Character::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void APersonalized_Character::DoInteract()
{
	if (OverlapActor != nullptr && OverlapActor->Implements<UInteractInterface>())
	{
		// GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Green,TEXT("Interact DO INTERACT"));
		IInteractInterface::Execute_Interact(OverlapActor, this);
	}
}

void APersonalized_Character::OnMakeDamage_Implementation(int Amount, AActor* DamageCauser)
{
	// Aquí conectamos HealthComponent
	// if (GEngine)
	// {
	// 	// HealthComponent->CurrentHealth -= Amount;
	// 	GEngine -> AddOnScreenDebugMessage(
	// 		-1, 
	// 		2.f, 
	// 		FColor::Green, 
	// 		TEXT("MakeDamage: Amount of damage = " + FString::SanitizeFloat(Amount))
	// 		);
	// }
	
	// int currentHealth = HealthComponent->MinusHealth(20);

}

void APersonalized_Character::DeathEvent()
{
	Destroy();
}


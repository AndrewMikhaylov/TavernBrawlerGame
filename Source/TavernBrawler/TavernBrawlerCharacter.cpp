// Copyright Epic Games, Inc. All Rights Reserved.

#include "TavernBrawlerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Enemy/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATavernBrawlerCharacter

ATavernBrawlerCharacter::ATavernBrawlerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	leftHandSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hand_l_socket"));
	leftHandSocket->SetupAttachment(GetMesh());

	rightHandSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hand_r_socket"));
	rightHandSocket->SetupAttachment(GetMesh());

	PlayerInventory = CreateDefaultSubobject<UPlayerItemManager>(TEXT("InventorySystem"));
	PlayerInventory->SetupHandSockets(leftHandSocket, rightHandSocket);

	PlayerAttacker = CreateDefaultSubobject<UPlayerAttacker>(TEXT("AttackSystem"));
	PlayerAttacker->AttackEnded.AddUObject(this, &ATavernBrawlerCharacter::StopAttacking);

	ActorHealthSystem = CreateDefaultSubobject<UActorHealthSystem>(TEXT("HealthSystem"));
	ActorHealthSystem->ActorDied.AddUObject(this, &ATavernBrawlerCharacter::InitateDeath);
}

void ATavernBrawlerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATavernBrawlerCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATavernBrawlerCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATavernBrawlerCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATavernBrawlerCharacter::LookInput);

		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoDodge);

		EnhancedInputComponent->BindAction(TakeThrowAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoTakeThrow);
		EnhancedInputComponent->BindAction(TakeWeaponAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoTakeWeapon);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoThrow);

		EnhancedInputComponent->BindAction(HitAction, ETriggerEvent::Started, this, &ATavernBrawlerCharacter::DoHit);
		IsReadyToAttack=true;

		

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATavernBrawlerCharacter::InitateDeath()
{
	//if player game over if oponent drop current item and die
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	if (AIController)
	{
		AIController->SetIsDead();
	}
}

void ATavernBrawlerCharacter::ResetAttackCooldown()
{
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &ATavernBrawlerCharacter::GetReadyToAttack, .3f, false);
}

void ATavernBrawlerCharacter::GetReadyToAttack()
{
	IsReadyToAttack=true;
}


float ATavernBrawlerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float appliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	OnFirstDamageTaken.Broadcast();
	ActorHealthSystem->TakeDamage(appliedDamage);
	return appliedDamage;
}

bool ATavernBrawlerCharacter::CheckIsAlive()
{
	return ActorHealthSystem->IsCharacterAlive();
}

void ATavernBrawlerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActorHealthSystem->SetHealth();
}

void ATavernBrawlerCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ATavernBrawlerCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ATavernBrawlerCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ATavernBrawlerCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ATavernBrawlerCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ATavernBrawlerCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ATavernBrawlerCharacter::DoDodge()
{
	if (CanDodge && !(GetCharacterMovement()->IsFalling()))
	{
		FVector DodgeDirection = CalculateDodgeDirection();

		CanDodge = false;

		LaunchCharacter(DodgeDirection*DodgeForce, true, false);

		FTimerHandle timer;
		GetWorldTimerManager().SetTimer(timer, this, &ATavernBrawlerCharacter::ResetDodgeTimer, DodgeCooldown, false);
	}
}

FVector ATavernBrawlerCharacter::CalculateDodgeDirection()
{
	FVector dodgeDirection = GetCharacterMovement()->GetLastInputVector();
	if (dodgeDirection.IsNearlyZero())
	{
		dodgeDirection = GetActorForwardVector();
	}
	else
	{
		dodgeDirection.Normalize();
	}

	dodgeDirection.Z = 0;
	dodgeDirection.Normalize();

	return dodgeDirection;
}

void ATavernBrawlerCharacter::ResetDodgeTimer()
{
	CanDodge = true;
}

void ATavernBrawlerCharacter::DoTakeThrow()
{
	PlayerInventory->TakeToThrow(FirstPersonCameraComponent->GetComponentLocation(), FirstPersonCameraComponent->GetForwardVector());
}

void ATavernBrawlerCharacter::DoTakeWeapon()
{
	PlayerInventory->TakeToFight(FirstPersonCameraComponent->GetComponentLocation(), FirstPersonCameraComponent->GetForwardVector());
}

void ATavernBrawlerCharacter::DoThrow()
{
	PlayerInventory->Throw(GetActorForwardVector());
}

void ATavernBrawlerCharacter::DoHit()
{
	if (IsReadyToAttack)
	{
		PlayerAttacker->DoHitMovement(PlayerInventory->GetCurrentFightItem());
		PlayerInventory->BeginHitting();
		IsReadyToAttack=false;	
	}
}

void ATavernBrawlerCharacter::StopAttacking()
{
	PlayerInventory->EndAttack();
	ResetAttackCooldown();
}

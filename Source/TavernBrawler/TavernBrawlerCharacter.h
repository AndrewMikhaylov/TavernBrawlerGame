// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InventorySystem/PlayerItemManager.h"
#include "AttackSystem/PlayerAttacker.h"
#include "Health/ActorHealthSystem.h"
#include "TavernBrawlerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class ATavernBrawlerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	class UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, Category = "Dodge")
	float DodgeForce;
	UPROPERTY(EditAnywhere, Category = "Dodge")
	float DodgeCooldown = 1.0f;
	bool CanDodge = true;
	UPROPERTY(EditAnywhere, Category = "Dodge")
	bool IsDodging;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TakeThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TakeWeaponAction;

	UPROPERTY(EditAnywhere, Category = "Attacker")
	UPlayerAttacker* PlayerAttacker;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* HitAction;
	
public:
	ATavernBrawlerCharacter();
	
	UPROPERTY(VisibleAnywhere)

	UStaticMeshComponent* leftHandSocket;

	UPROPERTY(VisibleAnywhere)

	UStaticMeshComponent* rightHandSocket;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	DECLARE_MULTICAST_DELEGATE(FOnFirstDamageTaken)
	FOnFirstDamageTaken OnFirstDamageTaken;

	bool CheckIsAlive();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoThrow();

	UPROPERTY(EditAnywhere, Category = "Inventory")
	UPlayerItemManager* PlayerInventory;

protected:

	virtual void BeginPlay() override;

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	void DoDodge();
	FVector CalculateDodgeDirection();

	void ResetDodgeTimer();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoTakeThrow();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoTakeWeapon();
	

	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoHit();

	void StopAttacking();

	void UpdateHUD();

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	UActorHealthSystem* ActorHealthSystem;	
	void InitateDeath();

	
	bool IsReadyToAttack;
	void ResetAttackCooldown();
	void GetReadyToAttack();
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};


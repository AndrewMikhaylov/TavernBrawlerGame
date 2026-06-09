// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/InteractableItem.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hurtMesh = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HurtBox"));
	SetRootComponent(hurtMesh);
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	visualMesh->SetupAttachment(hurtMesh);
}

// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeItem();

}

// Called every frame
void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableItem::Throw(FVector Direction)
{
	IsThrown = true;
	hurtMesh->SetSimulatePhysics(true);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	FVector ThrowDirection = Direction + FVector(0.0f, 0.0f, 0.4f);
	ThrowDirection.Normalize();
	hurtMesh->AddImpulse(ThrowDirection*ItemData->ThrowStrength, NAME_None, true);

	hurtMesh->OnComponentHit.AddDynamic(this, &AInteractableItem::DealThrowDamage);
}


void AInteractableItem::DealHitDamage()
{
	//deal damage, if succesfull
	CurrentDurability--;
	if (CurrentDurability==0)
	{
		BreakItem();
	}
}

void AInteractableItem::DealThrowDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsThrown)
	{
		//deal damage
		if (CurrentDurability > 1)
		{
			CurrentDurability = 1;
			BreakTransformItem();
		}
		else
		{
			BreakItem();
		}
	}
	IsThrown = false;

	hurtMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	hurtMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	hurtMesh->OnComponentHit.Clear();
	hurtMesh->SetSimulatePhysics(false);
}

void AInteractableItem::PickUp()
{

}

void AInteractableItem::InitializeItem()
{
	visualMesh->SetStaticMesh(ItemData->UnbrokenVisualMesh);
	CurrentDamage = ItemData->UnbrokenHitDamage;
	CurrentThrowDamage = ItemData->UnbrokenThrowDamage;
	CurrentDurability = ItemData->Durability;
}

void AInteractableItem::BreakTransformItem()
{
	visualMesh->SetStaticMesh(ItemData->BrokenVisualMesh);
	CurrentDamage = ItemData->BrokenHitDamage;
	CurrentThrowDamage = ItemData->BrokenThrowDamage;
	CurrentDurability = 1;
}

void AInteractableItem::BreakItem()
{
	OnItemBroken.Broadcast();

	Destroy();
}


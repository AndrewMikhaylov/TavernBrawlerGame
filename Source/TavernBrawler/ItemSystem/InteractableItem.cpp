// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/InteractableItem.h"

#include "TavernBrawlerCharacter.h"
#include "TavernBrawlerGameMode.h"
#include "Engine/DamageEvents.h"
#include "World/ObjectPool/ObjectPoolSubsystem.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hurtMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	SetRootComponent(hurtMesh);
	visualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	visualMesh->SetupAttachment(hurtMesh);
}

// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeItem();
	hurtMesh->OnComponentHit.AddDynamic(this, &AInteractableItem::DealThrowDamage);
	hurtMesh->OnComponentBeginOverlap.AddDynamic(this, &AInteractableItem::OnOverlapBegin);
	visualMesh->SetGenerateOverlapEvents(false);
	visualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	hurtMesh->SetGenerateOverlapEvents(true);
	hurtMesh->SetNotifyRigidBodyCollision(true);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionParameters = hurtMesh->GetCollisionResponseToChannels();
}

// Called every frame
void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsAttacking && !ActorsHit.Contains(OtherActor))
	{
		FPointDamageEvent DamageEvent;
		ATavernBrawlerCharacter* damageReceiver = Cast<ATavernBrawlerCharacter>(OtherActor);
		if (damageReceiver)
		{
			damageReceiver->TakeDamage(ItemData->HitDamage,
				DamageEvent,
				ThisItemOwner->GetInstigatorController(),
				this);	
		}
		CurrentDurability--;
		if (CurrentDurability>0)
		{
			PlaySound();
		}
		ActorsHit.Add(OtherActor);
	}
}

void AInteractableItem::Throw(FVector Direction)
{
	IsThrown = true;
	hurtMesh->SetSimulatePhysics(true);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	hurtMesh->SetNotifyRigidBodyCollision(true);
	FVector ThrowDirection = Direction + 
			ThisItemOwner->GetActorRightVector()*0.2 +
			ThisItemOwner->GetActorUpVector()*0.2;
	ThrowDirection.Normalize();
	hurtMesh->AddImpulse(ThrowDirection*ItemData->ThrowStrength, NAME_None, true);
}


void AInteractableItem::BeginHitOnOverlap()
{
	IsAttacking = true;
	ActorsHit.Empty();
	hurtMesh->SetGenerateOverlapEvents(true);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	hurtMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

}

void AInteractableItem::DealThrowDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsThrown)
	{
		FPointDamageEvent DamageEvent;
		ATavernBrawlerCharacter* damageReceiver = Cast<ATavernBrawlerCharacter>(OtherActor);
		if (damageReceiver)
		{
			damageReceiver->TakeDamage(ItemData->ThrowDamage,
				DamageEvent,
				ThisItemOwner->GetInstigatorController(),
				this);	
		}
		if (CurrentDurability > 1)
		{
			CurrentDurability = 1;
			PlaySound();
		}
		else
		{
			BreakTransformItem();
		}
		IsThrown = false;
		ThisItemOwner=nullptr;
	
	hurtMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	hurtMesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

	}
}

void AInteractableItem::PickUp(AActor* ItemOwner)
{
	ThisItemOwner = ItemOwner;
	hurtMesh->SetSimulatePhysics(false);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AInteractableItem::DeactivateOverlap()
{
	IsAttacking = false;
	hurtMesh->SetGenerateOverlapEvents(false);
	hurtMesh->SetCollisionResponseToChannels(CollisionParameters);
	hurtMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	if (CurrentDurability==0)
	{
		BreakTransformItem();
	}
	
}

void AInteractableItem::Activate(bool isActive)
{
	Super::Activate(isActive);
	ATavernBrawlerGameMode* gameMode = Cast<ATavernBrawlerGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		OnItemSoundPlay.AddUObject(gameMode, &ATavernBrawlerGameMode::PlaySoundAtLocation);
	}
}

void AInteractableItem::InitializeItem()
{
	visualMesh->SetStaticMesh(ItemData->VisualMesh);
	CurrentDamage = ItemData->HitDamage;
	CurrentThrowDamage = ItemData->ThrowDamage;
	CurrentDurability = ItemData->Durability;
}

void AInteractableItem::BreakTransformItem()
{
	FTransform SpawnLocation = GetActorTransform();
	PlaySound();
	TArray<AInteractableItem*> Items;
	if (ItemData->BrokenActors.Num()>=1)
	{
		for (const TSubclassOf<AActor>& BrokenItem : ItemData->BrokenActors)
		{
			Items.Add(GetWorld()->SpawnActor<AInteractableItem>(BrokenItem, SpawnLocation));
		}
		int32 randomIndex = FMath::FRandRange(0.f,Items.Num()-1);
		nextItem = Items[randomIndex];	
	}
	BreakItem();
}

void AInteractableItem::BreakItem()
{
	ThisItemOwner = nullptr;
	OnItemBroken.Broadcast(nextItem);
	OnObjectDestroyed.Broadcast(Name, GetIndex());
}

void AInteractableItem::PlaySound()
{
	OnItemSoundPlay.Broadcast(ItemData->soundToPlay, GetActorLocation());
}


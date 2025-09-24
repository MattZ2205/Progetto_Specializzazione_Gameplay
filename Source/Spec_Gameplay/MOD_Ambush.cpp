// Fill out your copyright notice in the Description page of Project Settings.


#include "MOD_Ambush.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMOD_Ambush::AMOD_Ambush()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMOD_Ambush::OnAmbushTriggered);
}

void AMOD_Ambush::ActivateModifier(FVector Location, AActor* Target, ANPC* Giver)
{
	SetActorLocation(Location);
	actualTarget = Target;
}

// Called when the game starts or when spawned
void AMOD_Ambush::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMOD_Ambush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActivated)TimerToStop += DeltaTime;
	if (TimerToStop >= 5.f) StopModifier();
}

void AMOD_Ambush::StopModifier()
{
	actualTarget->SetActorHiddenInGame(false);
	actualTarget->SetActorEnableCollision(true);
	for (AActor* e : spawnedEnemies)
	{
		if (e) e->Destroy();
	}
	Destroy();
	bIsActivated = false;
}

void AMOD_Ambush::OnAmbushTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Red, TEXT("Ambush Triggered!"));

	for (TSubclassOf<AActor> enemy : enemiesToSpawn)
	{
		if (enemy)
		{
			FVector spawnLocation = GetActorLocation() + FMath::VRand() * Trigger->GetUnscaledSphereRadius();
			spawnLocation.Z = GetActorLocation().Z;
			FRotator spawnRotation = FRotator::ZeroRotator;
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AActor* e = GetWorld()->SpawnActor<AActor>(enemy, spawnLocation, spawnRotation, spawnParams);
			if (e)spawnedEnemies.Add(e);
			if (GEngine)
			{
				if (e) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Red, TEXT("Enemies spawned"));
				else GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Red, TEXT("Enemies NOT spawned"));
			}
		}
	}
	bIsActivated = true;

	actualTarget->SetActorHiddenInGame(true);
	actualTarget->SetActorEnableCollision(false);

	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
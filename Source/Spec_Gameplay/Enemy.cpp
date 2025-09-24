// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::Kill);
}

void AEnemy::SetQuestTarget(ANPC* Giver)
{
	QuestGiver = Giver;
}

void AEnemy::NotifyQuestCompletion()
{
	QuestGiver->WaitPlayerReturn();
	Destroy();
}

void AEnemy::Kill(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Orange, TEXT("Fight started!"));
	bInteracted = true;
	TriggerSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInteracted) TimerImplosion += DeltaTime;
	if (TimerImplosion >= 5.f)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Orange, TEXT("Enemy Imploded!"));
		NotifyQuestCompletion();
	}
}


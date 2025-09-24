// Fill out your copyright notice in the Description page of Project Settings.

#include "DeliveryNPC.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADeliveryNPC::ADeliveryNPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ADeliveryNPC::Deliver);
}

// Called when the game starts or when spawned
void ADeliveryNPC::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADeliveryNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADeliveryNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADeliveryNPC::SetQuestTarget(ANPC* Giver)
{
	QuestGiver = Giver;
}

void ADeliveryNPC::NotifyQuestCompletion()
{
	QuestGiver->WaitPlayerReturn();
	Destroy();
}

void ADeliveryNPC::Deliver(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Blue, TEXT("Item Delivered!"));
	NotifyQuestCompletion();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableItem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACollectableItem::ACollectableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACollectableItem::CollectItem);
}

// Called when the game starts or when spawned
void ACollectableItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectableItem::SetQuestTarget(ANPC* Giver)
{
	QuestGiver = Giver;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, "Quest Target Set: " + QuestGiver->GetActorNameOrLabel());
}

void ACollectableItem::NotifyQuestCompletion()
{
	QuestGiver->WaitPlayerReturn();
	Destroy();
}

void ACollectableItem::CollectItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, TEXT("Item Collected!"));
	NotifyQuestCompletion();
}


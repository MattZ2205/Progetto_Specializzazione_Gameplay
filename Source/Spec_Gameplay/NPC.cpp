// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "QuestItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC::ANPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Triggero"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Interact);

	Quest.bIsQuestActive = false;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::AssignQuest(TSubclassOf<AActor> Target, FVector Location, TSubclassOf<AQuestModifier> QuestModifier)
{
	Quest.Target = Target;
	Quest.TargetLocation = Location;
	Quest.QuestModifier = QuestModifier;
	Quest.bIsQuestActive = true;
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ANPC::WaitPlayerReturn()
{
	Pointer->SetActorLocation(GetActorLocation());

	bIsWaitingForPlayer = true;
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ANPC::CompleteQuest()
{
	Pointer->Destroy();

	Quest.bIsQuestActive = false;
	bIsWaitingForPlayer = false;
	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, TEXT("Quest Completed!"));
}

void ANPC::StartQuest()
{
	Pointer = GetWorld()->SpawnActor<AActor>(
		PointerClass,
		Quest.TargetLocation,
		FRotator::ZeroRotator
	);

	FActorSpawnParameters spawnParams;
	//spawnParams.Name = MakeUniqueObjectName(GetWorld(), Quest.Target, FName("QuestTarget"));
	spawnParams.Owner = this;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* Target = GetWorld()->SpawnActor<AActor>(
		Quest.Target,
		Quest.TargetLocation,
		FRotator::ZeroRotator,
		spawnParams
	);
	if (Target && Target->GetClass()->ImplementsInterface(UQuestItem::StaticClass()))
	{
		IQuestItem* QuestItem = Cast<IQuestItem>(Target);
		if (QuestItem) QuestItem->SetQuestTarget(this);
	}

	//spawnParams.Name = MakeUniqueObjectName(GetWorld(), Quest.QuestModifier, FName("QuestModifier"));
	AQuestModifier* Modifier = GetWorld()->SpawnActor<AQuestModifier>(
		Quest.QuestModifier,
		Quest.TargetLocation,
		FRotator::ZeroRotator,
		spawnParams
	);
	if (Modifier) Modifier->ActivateModifier(Quest.TargetLocation, Target);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, Modifier->GetActorNameOrLabel());
		GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, Target->GetActorNameOrLabel());
		GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, Quest.TargetLocation.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, GetActorNameOrLabel());
	}

	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ANPC::Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsWaitingForPlayer) StartQuest();
	else CompleteQuest();
}
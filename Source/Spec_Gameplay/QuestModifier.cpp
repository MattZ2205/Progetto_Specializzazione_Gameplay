// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestModifier.h"

// Sets default values
AQuestModifier::AQuestModifier()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuestModifier::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQuestModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestModifier::ActivateModifier(FVector Location, AActor* Target, ANPC* Giver)
{
}

void AQuestModifier::StopModifier()
{
}

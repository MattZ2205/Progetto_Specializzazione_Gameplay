// Fill out your copyright notice in the Description page of Project Settings.

#include "MOD_TimeOfTheDay.h"
#include "Kismet/GameplayStatics.h"

void AMOD_TimeOfTheDay::ActivateModifier(FVector Location, AActor* Target, ANPC* Giver)
{
	DayManager = Cast<ADayManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADayManager::StaticClass()));

	actualGiver = Giver;

	actualTarget = Target;
	actualTarget->SetActorHiddenInGame(true);
	actualTarget->SetActorEnableCollision(false);
}

void AMOD_TimeOfTheDay::StopModifier()
{
	Destroy();
}

void AMOD_TimeOfTheDay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (actualGiver->bIsWaitingForPlayer) StopModifier();

	if (TargetDayMoment == DayManager->DayMomentEnum)
	{
		actualTarget->SetActorHiddenInGame(false);
		actualTarget->SetActorEnableCollision(true);
	}
	else
	{
		actualTarget->SetActorHiddenInGame(true);
		actualTarget->SetActorEnableCollision(false);
	}
}
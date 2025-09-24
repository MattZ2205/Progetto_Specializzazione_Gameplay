// Fill out your copyright notice in the Description page of Project Settings.

#include "MOD_TimeOfTheDay.h"
#include "QuestItem.h"
#include "Kismet/GameplayStatics.h"

void AMOD_TimeOfTheDay::ActivateModifier(FVector Location, AActor* Target)
{
	DayManager = Cast<ADayManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ADayManager::StaticClass()));

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
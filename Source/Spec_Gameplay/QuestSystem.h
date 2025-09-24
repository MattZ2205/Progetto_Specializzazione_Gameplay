// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem.generated.h"

class AQuestModifier;

USTRUCT(BlueprintType)
struct FQuestSystem
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AActor> Target;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	TSubclassOf<AQuestModifier> QuestModifier;

	UPROPERTY()
	bool bIsQuestActive;
};
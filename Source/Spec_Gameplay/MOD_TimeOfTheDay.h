// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestItem.h"
#include "DayManager.h"
#include "CoreMinimal.h"
#include "QuestModifier.h"
#include "MOD_TimeOfTheDay.generated.h"

/**
 *
 */
UCLASS()
class SPEC_GAMEPLAY_API AMOD_TimeOfTheDay : public AQuestModifier
{
	GENERATED_BODY()

public:
	virtual void ActivateModifier(FVector Location, AActor* Target, ANPC* Giver) override;

private:
	virtual void StopModifier() override;

protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AActor* actualTarget;

	UPROPERTY()
	ADayManager* DayManager;

	UPROPERTY(EditAnywhere)
	EDayMoment TargetDayMoment;

	UPROPERTY()
	ANPC* actualGiver;

};
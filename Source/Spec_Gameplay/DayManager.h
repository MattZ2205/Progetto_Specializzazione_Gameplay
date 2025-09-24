// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayManager.generated.h"

UENUM(BlueprintType)
enum class EDayMoment : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Morning = 1 UMETA(DisplayName = "Morning"),
	Afternoon = 2 UMETA(DisplayName = "Afternoon"),
	Evening = 3 UMETA(DisplayName = "Evening"),
	Night = 4 UMETA(DisplayName = "Night")
};

UCLASS()
class SPEC_GAMEPLAY_API ADayManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADayManager();

	UFUNCTION()
	void SetDayMoment();

private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	EDayMoment DayMomentEnum = EDayMoment::Morning;

private:
	UPROPERTY()
	float ActualDayMoment;

	UPROPERTY(EditAnywhere)
	float QuarterLength;

	UPROPERTY(EditAnywhere)
	AQuestManager* QuestManager;

};

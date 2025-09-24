// Fill out your copyright notice in the Description page of Project Settings.


#include "DayManager.h"

// Sets default values
ADayManager::ADayManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActualDayMoment += DeltaTime;
	if ((ActualDayMoment / (float)DayMomentEnum) >= QuarterLength)
	{
		SetDayMoment();
		QuestManager->AssignQuestToNPCS();
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::SanitizeFloat(ActualDayMoment));
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDayMoment"), true);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, EnumPtr->GetNameStringByValue((int64)DayMomentEnum));
}

void ADayManager::SetDayMoment()
{
	if (ActualDayMoment > QuarterLength && ActualDayMoment < (QuarterLength * 2)) DayMomentEnum = EDayMoment::Afternoon;
	else if (ActualDayMoment > (QuarterLength * 2) && ActualDayMoment < (QuarterLength * 3)) DayMomentEnum = EDayMoment::Evening;
	else if (ActualDayMoment > (QuarterLength * 3) && ActualDayMoment < (QuarterLength * 4)) DayMomentEnum = EDayMoment::Night;
	else
	{
		DayMomentEnum = EDayMoment::Morning;
		ActualDayMoment = 0.f;
	}
}
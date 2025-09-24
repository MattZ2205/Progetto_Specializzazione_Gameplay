// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManager.h"

// Sets default values
AQuestManager::AQuestManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

#pragma region DA CANCELLARE
//DA CALLARE : Metodo di debug
void AQuestManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	FlushPersistentDebugLines(GetWorld());

	for (const FLocations& Loc : Locations)
	{
		DrawDebugBox(
			GetWorld(),
			Loc.Location,
			FVector(10.0f, 10.0f, 10.0f),
			FQuat::Identity,
			FColor::Red,
			true,
			0.0f
		);
	}
}
#pragma endregion

void AQuestManager::GenerateQuest(ANPC* QuestGiver)
{
	EQuestType actualCat = PickCat();

	FLocations ChosenLocation;
	if (!GetRandomIndexFromCat(actualCat, Locations, &ChosenLocation)) return;

	FTargets ChosenTarget;
	if (!GetRandomIndexFromCat(actualCat, Targets, &ChosenTarget)) return;


	FModifiers ChosenModifier;
	if (!GetRandomIndexFromCat(actualCat, Modifiers, &ChosenModifier)) return;

	QuestGiver->AssignQuest(ChosenTarget.Target, ChosenLocation.Location, ChosenModifier.Modifier);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.9f, FColor::Green, "Quest assegnata: " + QuestGiver->GetActorNameOrLabel());
}

template<typename T>
bool AQuestManager::GetRandomIndexFromCat(EQuestType type, TArray<T>& array, T* out, int NTry)
{
	if (array.Num() == 0) return false;
	if (NTry >= 50) return false;

	int32 i = FMath::RandRange(0, array.Num() - 1);

	if (array[i].type == type && !array[i].bIsTaken) {
		array[i].bIsTaken = true;
		*out = array[i];
		return true;
	}
	else return GetRandomIndexFromCat(type, array, out, NTry + 1);
}

void AQuestManager::AssignQuestToNPCS()
{
	TArray<int> n;
	for (int i = 0; i < NPCS.Num(); i++)
	{
		if (!NPCS[i]->Quest.bIsQuestActive)
		{
			ResetTakenFlags(i);
			n.Add(i);
		}
	}

	if (NPCS.Num() - n.Num() < MaxActiveQuests - NQuestRange)
	{
		int NQuestToActivate = FMath::RandRange(MaxActiveQuests - NQuestRange, MaxActiveQuests) - (NPCS.Num() - n.Num());
		for (int i = 0; i < NQuestToActivate; i++)
		{
			int ind = FMath::RandRange(0, n.Num() - 1);
			GenerateQuest(NPCS[n[ind]]);
			n.RemoveAt(ind);
		}
	}
}

EQuestType AQuestManager::PickCat()
{
	return EQuestType(FMath::RandRange(0, 2));
}

void AQuestManager::ResetTakenFlags(int ind)
{
	for (int i = 0; i < Locations.Num(); i++)
	{
		if (NPCS[ind]->Quest.TargetLocation == Locations[i].Location) Locations[i].bIsTaken = false;
	}

	for (int i = 0; i < Targets.Num(); i++)
	{
		if (NPCS[ind]->Quest.Target == Targets[i].Target) Targets[i].bIsTaken = false;
	}

	for (int i = 0; i < Targets.Num(); i++)
	{
		if (NPCS[ind]->Quest.QuestModifier == Modifiers[i].Modifier) Modifiers[i].bIsTaken = false;
	}
}

// Called when the game starts or when spawned
void AQuestManager::BeginPlay()
{
	Super::BeginPlay();
	AssignQuestToNPCS();
}

// Called every frame
void AQuestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPC.h"
#include "QuestModifier.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestManager.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Collection  UMETA(DisplayName = "Collection"),
	Killing     UMETA(DisplayName = "Killing"),
	Delivery    UMETA(DisplayName = "Delivery")
};

USTRUCT(BlueprintType)
struct FLocations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector Location;

	UPROPERTY(EditAnywhere)
	EQuestType type;

	UPROPERTY()
	bool bIsTaken = false;
};

USTRUCT(BlueprintType)
struct FTargets
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Target;

	UPROPERTY(EditAnywhere)
	EQuestType type;

	UPROPERTY()
	bool bIsTaken = false;
};

USTRUCT(BlueprintType)
struct FModifiers
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AQuestModifier> Modifier;

	UPROPERTY(EditAnywhere)
	EQuestType type;

	UPROPERTY()
	bool bIsTaken = false;
};

UCLASS()
class SPEC_GAMEPLAY_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestManager();

	UFUNCTION()
	void AssignQuestToNPCS();

private:
	UFUNCTION()
	void GenerateQuest(ANPC* QuestGiver);

	UFUNCTION()
	EQuestType PickCat();

	//DA CANCELLARE : Metodi di debug
	virtual void OnConstruction(const FTransform& Transform) override;

	template<typename T>
	bool GetRandomIndexFromCat(EQuestType type, TArray<T>& array, T* out, int NTry = 0);

	UFUNCTION()
	void ResetTakenFlags(int ind);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<FLocations> Locations;

	UPROPERTY(EditAnywhere)
	TArray<FTargets> Targets;

	UPROPERTY(EditAnywhere)
	TArray<FModifiers> Modifiers;

	UPROPERTY(EditAnywhere)
	TArray<ANPC*> NPCS;

	UPROPERTY(EditAnywhere)
	int MaxActiveQuests;

	UPROPERTY(EditAnywhere)
	int NQuestRange;
};
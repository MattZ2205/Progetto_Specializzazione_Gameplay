// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "QuestSystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
	Farmer     UMETA(DisplayName = "Farmer"),
	Bourgeois  UMETA(DisplayName = "Bourgeois"),
	Knight     UMETA(DisplayName = "Knight"),
	Plebeian   UMETA(DisplayName = "Plebeian")
};

UCLASS()
class SPEC_GAMEPLAY_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AssignQuest(TSubclassOf<AActor> Target, FVector Location, TSubclassOf<AQuestModifier> QuestModifier);

	UFUNCTION()
	void WaitPlayerReturn();

private:
	UFUNCTION()
	void Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StartQuest();

	UFUNCTION()
	void CompleteQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
	FQuestSystem Quest;

private:
	UPROPERTY(EditAnywhere)
	USphereComponent* Trigger;

	UPROPERTY(EditAnywhere)
	ENPCType NPCType;

	UPROPERTY()
	bool bIsWaitingForPlayer;
};

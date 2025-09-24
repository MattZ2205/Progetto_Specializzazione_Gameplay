// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestModifier.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOD_Ambush.generated.h"

UCLASS()
class SPEC_GAMEPLAY_API AMOD_Ambush : public AQuestModifier
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMOD_Ambush();

	virtual void ActivateModifier(FVector Location, AActor* Target, ANPC* Giver) override;

private:
	UFUNCTION()
	void OnAmbushTriggered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void StopModifier() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AActor* actualTarget;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Trigger;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> enemiesToSpawn;

	UPROPERTY()
	TArray<AActor*> spawnedEnemies;

	bool bIsActivated = false;
	float TimerToStop;

};

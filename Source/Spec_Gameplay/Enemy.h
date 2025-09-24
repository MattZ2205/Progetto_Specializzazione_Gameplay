// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestItem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SPEC_GAMEPLAY_API AEnemy : public AActor, public IQuestItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();

	UFUNCTION()
	void SetQuestTarget(ANPC* Giver) override;

private:
	UFUNCTION()
	void Kill(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void NotifyQuestCompletion() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* TriggerSphere;

private:
	UPROPERTY()
	ANPC* QuestGiver;

	bool bInteracted = false;
	float TimerImplosion = 0.0f;

};

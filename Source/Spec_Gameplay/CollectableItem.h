// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestItem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableItem.generated.h"

UCLASS()
class SPEC_GAMEPLAY_API ACollectableItem : public AActor, public IQuestItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectableItem();

	UFUNCTION()
	virtual void SetQuestTarget(ANPC* Giver) override;

	UFUNCTION()
	void CollectItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION()
	void NotifyQuestCompletion() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* TriggerBox;

private:
	UPROPERTY()
	ANPC* QuestGiver;

};

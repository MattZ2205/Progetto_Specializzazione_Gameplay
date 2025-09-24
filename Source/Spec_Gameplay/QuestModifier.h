// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestModifier.generated.h"

UCLASS(Abstract)
class SPEC_GAMEPLAY_API AQuestModifier : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestModifier();

	virtual void ActivateModifier(FVector Location, AActor* Target);

private:
	virtual void StopModifier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

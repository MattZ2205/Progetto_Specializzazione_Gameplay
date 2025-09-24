// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuestItem.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DeliveryNPC.generated.h"

UCLASS()
class SPEC_GAMEPLAY_API ADeliveryNPC : public ACharacter, public IQuestItem
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADeliveryNPC();

	UFUNCTION()
	void SetQuestTarget(ANPC* Giver) override;

private:
	UFUNCTION()
	void Deliver(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void NotifyQuestCompletion() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* TriggerSphere;

	UPROPERTY()
	ANPC* QuestGiver;

};

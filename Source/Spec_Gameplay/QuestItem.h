// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NPC.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestItem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestItem : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class SPEC_GAMEPLAY_API IQuestItem
{
	GENERATED_BODY()

public:
	virtual void SetQuestTarget(ANPC* Giver) = 0;

private:
	virtual void NotifyQuestCompletion() = 0;

};

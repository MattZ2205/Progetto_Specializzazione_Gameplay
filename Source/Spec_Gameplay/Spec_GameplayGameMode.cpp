// Copyright Epic Games, Inc. All Rights Reserved.

#include "Spec_GameplayGameMode.h"
#include "Spec_GameplayCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpec_GameplayGameMode::ASpec_GameplayGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

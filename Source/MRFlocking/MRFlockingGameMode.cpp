// Copyright Epic Games, Inc. All Rights Reserved.

#include "MRFlockingGameMode.h"
#include "MRFlockingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMRFlockingGameMode::AMRFlockingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

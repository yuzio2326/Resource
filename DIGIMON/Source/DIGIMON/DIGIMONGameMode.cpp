// Copyright Epic Games, Inc. All Rights Reserved.

#include "DIGIMONGameMode.h"
#include "DIGIMONCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADIGIMONGameMode::ADIGIMONGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamepadSandboxGameMode.h"
#include "GamepadSandboxCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamepadSandboxGameMode::AGamepadSandboxGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

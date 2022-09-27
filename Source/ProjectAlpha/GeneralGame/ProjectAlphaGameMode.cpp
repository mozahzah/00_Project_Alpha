// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAlpha/GeneralGame/ProjectAlphaGameMode.h"

#include "UObject/ConstructorHelpers.h"

AProjectAlphaGameMode::AProjectAlphaGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> MainCharacterBPClass (TEXT("/Game/BluePrints/MainCharacter/BP_ProjectAlphaMainCharacter.BP_ProjectAlphaMainCharacter_C"));
	if (MainCharacterBPClass.Class) 
	{
		DefaultPawnClass = MainCharacterBPClass.Class;
	}
}

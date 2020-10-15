// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAlphaGameMode.h"
#include "UObject/ConstructorHelpers.h"


AProjectAlphaGameMode::AProjectAlphaGameMode()
{
	//auto MainCharacterBPClass = TSubclassOf<AProjectAlphaMainCharacter>();
	static ConstructorHelpers::FClassFinder<APawn> MainCharacterBPClass (TEXT("/Game/BluePrints/MainCharacter/BP_ProjectAlphaMainCharacter.BP_ProjectAlphaMainCharacter_C"));
	if (!ensure(MainCharacterBPClass.Class)) return;
	DefaultPawnClass = MainCharacterBPClass.Class;
}


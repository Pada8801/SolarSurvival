// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SolarSurvival.h"
#include "SolarSurvivalGameMode.h"
#include "../SolarSurvival/HUD/SolarSurvivalHUD.h"
#include "../SolarSurvival/Controllers/PlayerController/SolarPlayerController.h"
#include "../SolarSurvival/GameState/SolarGameState.h"
#include "../SolarSurvival/PlayerState/SolarPlayerState.h"

ASolarSurvivalGameMode::ASolarSurvivalGameMode(const class FObjectInitializer& FOI)
	: Super(FOI)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("/Game/Blueprints/SolarDefaultCharacter"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	// use our custom HUD class
	HUDClass = ASolarSurvivalHUD::StaticClass();

	// setting our custom player controller
	PlayerControllerClass = ASolarPlayerController::StaticClass();
	GameStateClass = ASolarGameState::StaticClass();
	PlayerStateClass = ASolarPlayerState::StaticClass();
}

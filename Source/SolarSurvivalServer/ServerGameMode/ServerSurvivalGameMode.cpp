

#include "SolarSurvivalServer.h"
#include "../SolarSurvivalServer/ServerGameMode/ServerSurvivalGameMode.h"
#include "../SolarSurvivalServer/ServerGameSession/SurvivalGameSession.h"
#include "../SolarSurvival/HUD/SolarSurvivalHUD.h"
#include "../SolarSurvival/Controllers/PlayerController/SolarPlayerController.h"
#include "../SolarSurvival/GameState/SolarGameState.h"
#include "../SolarSurvival/PlayerState/SolarPlayerState.h"
#include "Runtime/SQLiteSupport/Public/SQLiteSupport.h"
#include "Runtime/SQLiteSupport/Public/SQLiteDatabaseConnection.h"


AServerSurvivalGameMode::AServerSurvivalGameMode(const class FObjectInitializer& FOI)
	: Super(FOI)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("/Game/Blueprints/SolarDefaultCharacter"));
	if (PlayerPawnObject.Object != NULL)
	{
		DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass;
	}

	//use our custom HUD class
	HUDClass = ASolarSurvivalHUD::StaticClass();

	// setting our custom player controller
	PlayerControllerClass = ASolarPlayerController::StaticClass();
	GameStateClass = ASolarGameState::StaticClass();
	PlayerStateClass = ASolarPlayerState::StaticClass();

	DisplayName = FText::FromString(TEXT("ServerSurvival"));

	//set startup settings
	bStartPlayersAsSpectators = false;

	//FSQLiteDatabase Database;
	//Database.Open(TEXT("test.db"), nullptr, nullptr);

}

TSubclassOf<AGameSession> AServerSurvivalGameMode::GetGameSessionClass() const
{
	return ASurvivalGameSession::StaticClass();
}

void AServerSurvivalGameMode::InitGameState()
{
	Super::InitGameState();

	SolarGameState = Cast<ASolarGameState>(GameState);

	if (GameSession != NULL && GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		GameSession->RegisterServer();
	}
}
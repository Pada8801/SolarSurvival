#include "SolarSurvivalServer.h"
#include "OnlineSessionSettings.h"
#include "../SolarSurvival/GameState/SolarGameState.h"
#include "SurvivalOnlineGameSettingsBase.h"

FSurvivalOnlineGameSettingsBase::FSurvivalOnlineGameSettingsBase(bool bIsLanGame, bool bIsPresense, int32 MaxNumberPlayers)
{
	NumPublicConnections = FMath::Max(MaxNumberPlayers, 0);
	NumPrivateConnections = 0;
	bIsLANMatch = bIsLanGame;

	bShouldAdvertise = true;
	bAllowJoinInProgress = true;
	bAllowInvites = true;
	bUsesPresence = bIsPresense;
	bAllowJoinViaPresence = bIsPresense; bAllowJoinViaPresenceFriendsOnly = bIsPresense;
}

void FSurvivalOnlineGameSettingsBase::ApplyGameSettings(AServerSurvivalGameMode *CurrentGame)
{
	bIsDedicated = CurrentGame->GetWorld()->GetNetMode() == NM_DedicatedServer;

	Set(SETTING_GAMEMODE, CurrentGame->GetClass()->GetPathName(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	Set(SETTING_GAMENAME, CurrentGame->DisplayName.ToString(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	Set(SETTING_MAPNAME, CurrentGame->GetWorld()->GetMapName(), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	if (CurrentGame->SolarGameState)
	{
		Set(SETTING_SERVERNAME, CurrentGame->SolarGameState->ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		Set(SETTING_SERVERMOTD, CurrentGame->SolarGameState->ServerMOTD, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	}

	Set(SETTING_PLAYERSONLINE, CurrentGame->NumPlayers, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
}
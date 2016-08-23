#pragma once

#include "ServerSurvivalGameMode.h"

#define SETTING_GAMENAME FName(TEXT("GAMENAME"))
#define SETTING_SERVERNAME FName(TEXT("SURVIVAL_SERVERNAME"))
#define SETTING_SERVERVERSION FName(TEXT("SURVIVAL_SERVERVERSION"))
#define SETTING_SERVERMOTD FName(TEXT("SURVIVAL_SERVERMOTD"))
#define SETTING_PLAYERSONLINE FName(TEXT("SURVIVAL_PLAYERONLINE"))
#define SETTING_SERVERFLAGS FName(TEXT("SURVIVAL_SERVERFLAGS"))

#define SERVERFLAG_RequiresPassword 0x00000001;

class FSurvivalOnlineGameSettingsBase : public FOnlineSessionSettings
{
public:
	FSurvivalOnlineGameSettingsBase(bool bIsLanGame = false, bool bIsPresense = false, int32 MaxNumberPlayers = 32);
	virtual ~FSurvivalOnlineGameSettingsBase(){}

	virtual void ApplyGameSettings(AServerSurvivalGameMode *CurrentGame);
};
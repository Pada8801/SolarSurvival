#include "SolarSurvivalServer.h"
#include "Online.h"
#include "OnlineSubsystemTypes.h"
#include "SurvivalGameSession.h"
#include "SurvivalOnlineGameSettingsBase.h"
#include "ServerSurvivalGameMode.h"





ASurvivalGameSession::ASurvivalGameSession(const class FObjectInitializer& FOI)
	: Super(FOI)
{

}

void ASurvivalGameSession::InitOptions(const FString &Options)
{
	Super::InitOptions(Options);

	SurvivalGameMode = Cast<AServerSurvivalGameMode>(GetWorld()->GetAuthGameMode());
}

void ASurvivalGameSession::RegisterServer()
{
	const auto OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub && GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		const auto SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			TSharedPtr<class FSurvivalOnlineGameSettingsBase> OnlineGameSettings = MakeShareable(new FSurvivalOnlineGameSettingsBase(false, false, 64));
			if (OnlineGameSettings.IsValid() && SurvivalGameMode)
			{
				OnlineGameSettings->ApplyGameSettings(SurvivalGameMode);
				SessionInterface->CreateSession(0, GameSessionName, *OnlineGameSettings);
				return;
			}
		}
	}
}
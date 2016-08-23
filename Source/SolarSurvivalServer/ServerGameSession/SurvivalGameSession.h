#pragma once

#include "ServerSurvivalGameMode.h"
#include "Online.h"
#include "SurvivalGameSession.generated.h"

UCLASS()
class ASurvivalGameSession : public AGameSession
{
	GENERATED_BODY()
public:
	ASurvivalGameSession(const FObjectInitializer&);

	AServerSurvivalGameMode *SurvivalGameMode;
	
	virtual void InitOptions(const FString &Options);
	virtual void RegisterServer();

};
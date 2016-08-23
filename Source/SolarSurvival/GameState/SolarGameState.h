#pragma once

#include "GameFramework/GameState.h"

#include "SolarGameState.generated.h"


UCLASS()
class SOLARSURVIVAL_API ASolarGameState : public AGameState
{
	GENERATED_UCLASS_BODY()
private:
protected:
public:
	/** server settings */
	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category = ServerInfo)
		FString ServerName;
	UPROPERTY(Replicated, Config, EditAnywhere, BlueprintReadWrite, Category = ServerInfo)
		FString ServerMOTD;
};
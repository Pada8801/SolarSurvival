

#pragma once

#include "GameFramework/GameMode.h"
#include "ServerSurvivalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSURVIVALSERVER_API AServerSurvivalGameMode : public AGameMode
{
	GENERATED_BODY()
private:
public:
	UPROPERTY()
	class ASolarGameState* SolarGameState;

	AServerSurvivalGameMode(const FObjectInitializer&);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Game)
	FText DisplayName;

	virtual void InitGameState() override;
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;
	
	
};

#include "SolarSurvival.h"
#include "SolarGameState.h"


ASolarGameState::ASolarGameState(const class FObjectInitializer& FOI)
: Super(FOI)
{

}

void ASolarGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASolarGameState, ServerName, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(ASolarGameState, ServerMOTD, COND_InitialOnly);
}
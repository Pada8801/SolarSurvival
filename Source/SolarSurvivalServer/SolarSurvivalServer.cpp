#include "SolarSurvivalServer.h"


void FSolarSurvivalServerModule::StartupModule()
{
	if (GEngine)
	{
		FString serverTest = "The server module is running";
 		GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Green, serverTest);
	}
}



IMPLEMENT_GAME_MODULE(FSolarSurvivalServerModule, SolarSurvivalServer);
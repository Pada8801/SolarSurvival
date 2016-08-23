#include "SolarSurvival.h"
#include "SolarGameSession.h"



ASolarGameSession::ASolarGameSession(const class FObjectInitializer& FOI)
: Super(FOI)
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ASolarGameSession::OnCreateSessionComplete);
	}
}

void ASolarGameSession::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{

}
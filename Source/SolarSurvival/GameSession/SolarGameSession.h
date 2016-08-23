#pragma once
#include "Online.h"
#include "SolarGameSession.generated.h"



UCLASS(config=Game)
class ASolarGameSession : public AGameSession
{
	GENERATED_UCLASS_BODY()
private:
protected:
	/* Online Session Delegates */

	/* This delegate is for creating a new session */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	/* This delegate is for after starting a session */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/* This delegate is for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/* This delegate is for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/* This delegate is for after joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

public:
};
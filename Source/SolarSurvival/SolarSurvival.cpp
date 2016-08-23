// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SolarSurvival.h"
//#include "SolarSurvival.generated.inl"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, SolarSurvival, "SolarSurvival" );

//General Log
DEFINE_LOG_CATEGORY(SolarLog);

//Logging during game startup
DEFINE_LOG_CATEGORY(SolarInit);

//Logging for your AI system
DEFINE_LOG_CATEGORY(SolarAI);

//Logging for Critical Errors that must always be addressed
DEFINE_LOG_CATEGORY(SolarCriticalErrors);
 
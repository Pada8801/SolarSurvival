// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __SOLARSURVIVAL_H__
#define __SOLARSURVIVAL_H__

#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"

#define COLLISION_PROJECTILE	ECC_GameTraceChannel1
#define COLISION_INTERACTION_CHECK	ECC_GameTraceChannel2



//General Log
DECLARE_LOG_CATEGORY_EXTERN(SolarLog, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(SolarInit, Log, All);

//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(SolarAI, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(SolarCriticalErrors, Log, All);

#endif

// Fill out your copyright notice in the Description page of Project Settings.

#include "SolarSurvival.h"
#include "AItemBase.h"




AAItemBase::AAItemBase(const class FObjectInitializer &FOI)
	:Super(FOI)
{
	itemName = FName(TEXT("DefaultItem"));
}
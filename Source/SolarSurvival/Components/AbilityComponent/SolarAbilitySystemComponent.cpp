// Fill out your copyright notice in the Description page of Project Settings.

#include "SolarSurvival.h"
#include "SolarAbilitySystemComponent.h"
#include "SolarSurvival/Abilitys/Stats/Character/UCharacterAttributeSet.h"






UCharacterAttributeSet* USolarAbilitySystemComponent::GetCharacterAttributes()
{
	for (UAttributeSet* Set : SpawnedAttributes)
	{
		if (Set && Set->IsA(UCharacterAttributeSet::StaticClass()))
		{
			return Cast<UCharacterAttributeSet>(Set);
		}
	}
	return NULL;
}


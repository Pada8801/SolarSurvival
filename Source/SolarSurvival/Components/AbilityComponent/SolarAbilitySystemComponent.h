// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "SolarAbilitySystemComponent.generated.h"

/**
 * 
 */

class UCharacterAttributeSet;


UCLASS(ClassGroup = SolarSurvival, meta = (BlueprintSpawnableComponent))
class SOLARSURVIVAL_API USolarAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UCharacterAttributeSet* GetCharacterAttributes();
	
};

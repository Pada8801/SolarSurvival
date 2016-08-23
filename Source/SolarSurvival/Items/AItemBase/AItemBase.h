// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AItemBase.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSURVIVAL_API AAItemBase : public AActor
{
	GENERATED_BODY()
private:
protected:
public:

	AAItemBase(const FObjectInitializer&);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName itemName;
	
	
};

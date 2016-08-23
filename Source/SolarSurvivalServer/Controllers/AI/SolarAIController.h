// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SolarAIController.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSURVIVALSERVER_API ASolarAIController : public AAIController
{
	GENERATED_BODY()
public:

	ASolarAIController(const FObjectInitializer&);

	UPROPERTY(transient)
	UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
	UBehaviorTreeComponent *BehaviorComp;

	virtual void Possess(class APawn* InPawn) override;

	virtual void BeginInactiveState() override;

	void Respawn();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetEnemy(class APawn* InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	class APawn* GetEnemy() const;


	UFUNCTION(BlueprintCallable, Category = Behavior)
	bool PawnCanBeSeen(APawn *Target);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemyInView();

protected:
	int32 EnemyKeyID;
	int32 SelfKeyID;
	
	
};

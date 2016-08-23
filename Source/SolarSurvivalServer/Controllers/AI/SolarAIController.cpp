// Fill out your copyright notice in the Description page of Project Settings.

#include "SolarSurvivalServer.h"
#include "SolarAIController.h"
#include "../SolarSurvival/Monsters/SolarBaseMonster/SolarBaseMonster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "SQLiteDatabaseConnection.h"



ASolarAIController::ASolarAIController(const class FObjectInitializer& FOI)
{ 
	BlackboardComp = FOI.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	BehaviorComp = FOI.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;
}

void ASolarAIController::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	ASolarBaseMonster* Monster = Cast<ASolarBaseMonster>(InPawn);

	if (Monster && Monster->BotBehavior && BlackboardComp && BehaviorComp)
	{
		BlackboardComp->InitializeBlackboard(*Monster->BotBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		SelfKeyID = BlackboardComp->GetKeyID("SelfActor");

		BehaviorComp->StartTree(*Monster->BotBehavior);
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(SelfKeyID, this->GetPawn());

	}
}

void ASolarAIController::BeginInactiveState()
{
	Super::BeginInactiveState();

	// Handle respawn logic here for monster

	BlackboardComp->SetValue <UBlackboardKeyType_Object>(EnemyKeyID, NULL);
}

void ASolarAIController::Respawn()
{
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

void ASolarAIController::SetEnemy(APawn *InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
	}
}

APawn *ASolarAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<APawn>(BlackboardComp->GetValueAsObject("Enemy"));
	}
	return NULL;
}

bool ASolarAIController::PawnCanBeSeen(APawn *InPawn)
{
	return false;
}

void ASolarAIController::SearchForEnemyInView()
{
}
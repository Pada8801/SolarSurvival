#include "SolarSurvival.h"
#include "SolarBaseMonster.h"



FMonsterVitals::FMonsterVitals()
{
	fCurrentHP = 1500.0f;
	fMaxHP = 1500.0f;

	fCurrentStamina = 1500.0f;
	fMaxStamina = 1500.0f;

	fCurrentHunger = 1500.0f;
	fMaxHunger = 1500.0f;
}


ASolarBaseMonster::ASolarBaseMonster(const class FObjectInitializer& FOI)
: Super(FOI)
{

}

void ASolarBaseMonster::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASolarBaseMonster, monsterVitals);
}

FMonsterVitals ASolarBaseMonster::GetMonsterVitals()
{
		return monsterVitals;
}
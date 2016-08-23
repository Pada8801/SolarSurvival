#pragma once

#include "SolarBaseMonster.generated.h"


USTRUCT()
struct FMonsterVitals
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fCurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fCurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fMaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fCurrentHunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vitals")
	float fMaxHunger;

	FMonsterVitals();
};

UCLASS(config = Game)
class SOLARSURVIVAL_API ASolarBaseMonster : public ACharacter
{
	GENERATED_UCLASS_BODY()

#pragma region Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Vitals)
	FMonsterVitals monsterVitals;
private:
public:

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

#pragma endregion Variables

#pragma region Functions
protected:
private:
public:
	FMonsterVitals GetMonsterVitals();
#pragma endregion Functions
};
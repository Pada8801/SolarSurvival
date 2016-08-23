#include "SolarSurvival.h"


#include "UCharacterAttributeSet.h"






UCharacterAttributeSet::UCharacterAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Health = MaxHealth = 100.f;
	Mana = MaxMana = 100.f;
	Sanity = MaxSanity = 100.f;

	Damage = 0.f;
	CritChance = 0.f;
	SpellDamage = 0.f;
	PhysicalDamage = 0.f;
	Strength = 0.f;
}


void UCharacterAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{

}

bool UCharacterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data)
{
	return true;
}


void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(UCharacterAttributeSet, MaxHealth);
	DOREPLIFETIME(UCharacterAttributeSet, Health);
	DOREPLIFETIME(UCharacterAttributeSet, MaxMana);
	DOREPLIFETIME(UCharacterAttributeSet, Mana);
	DOREPLIFETIME(UCharacterAttributeSet, MaxSanity);
	DOREPLIFETIME(UCharacterAttributeSet, Sanity);

	DOREPLIFETIME(UCharacterAttributeSet, SpellDamage);
	DOREPLIFETIME(UCharacterAttributeSet, PhysicalDamage);

	DOREPLIFETIME(UCharacterAttributeSet, CritChance);
	DOREPLIFETIME(UCharacterAttributeSet, CritMultiplier);
	DOREPLIFETIME(UCharacterAttributeSet, ArmorDamageReduction);

	DOREPLIFETIME(UCharacterAttributeSet, DodgeChance);

	DOREPLIFETIME(UCharacterAttributeSet, Strength);
}
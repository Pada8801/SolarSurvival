#pragma once
#include "AttributeSet.h"

#include "UCharacterAttributeSet.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (HideInDetailsView))
class UCharacterAttributeSet : public UAttributeSet
{
	GENERATED_UCLASS_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes", meta = (HideFromModifiers))			// You can't make a GameplayEffect modify Health Directly (go through)
		float	MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes", meta = (HideFromModifiers))			// You can't make a GameplayEffect modify Health Directly (go through)
		float	Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	MaxSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	Sanity;

	/** This Damage is just used for applying negative health mods. Its not a 'persistent' attribute. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes", meta = (HideFromLevelInfos))		// You can't make a GameplayEffect 'powered' by Damage (Its transient)
		float	Damage;

	/** This Attribute is the actual spell damage for this actor. It will power spell based GameplayEffects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	SpellDamage;

	/** This Attribute is the actual physical damage for this actor. It will power physical based GameplayEffects */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	PhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	CritChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	CritMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	ArmorDamageReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	DodgeChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "CharacterAttributes")
		float	Strength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterAttributes")
		float	TestAttribute;

	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
};

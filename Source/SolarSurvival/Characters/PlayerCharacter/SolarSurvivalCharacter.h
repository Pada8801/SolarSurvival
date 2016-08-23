// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SolarSurvivalCharacter.generated.h"


USTRUCT()
struct FVitals
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fCurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fMaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fCurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fMaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fCurrentHunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fMaxHunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fCurrentThirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fMaxThirst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fCurrentSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Vitals")
	float fMaxSanity;

	FVitals();
	void ModifyHP(float fModHP);
};

UCLASS(config = Game)
class ASolarSurvivalCharacter : public ACharacter
{
public:
	GENERATED_BODY()

	ASolarSurvivalCharacter(const FObjectInitializer&);

#pragma region Base Unreal Variables

		/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent *CharacterMesh;

	/** First person camera */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
//	TSubobjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASolarSurvivalProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

#pragma endregion Base Unreal Variables

#pragma region Protected Functions
protected:

	/** Handler for a touch input beginning. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	// End of APawn interface



#pragma endregion Protected Functions

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Vitals)
	FVitals characterVitals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Interaction)
	class USurvivalInteractive *interactiveComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Abilitys)
	class USolarAbilitySystemComponent *abilityComponent;

	UFUNCTION()
	void DoSanityChecks();

#pragma region Public Functions
public:

	/*Debug function*/
	void Debug();

	UFUNCTION(Reliable, server, WithValidation)
	void ServerOnFire();
	bool ServerOnFire_Validate();
	void ServerOnFire_Implementation();

	/** The start of object interaction */
	void Interact();

	UFUNCTION(Reliable, server, WithValidation)
	void Server_Interact();
	bool Server_Interact_Validate();
	void Server_Interact_Implementation();

	USurvivalInteractive *GetInteractionComponent();
	USolarAbilitySystemComponent* GetAbilitySystemComponent();

	FVitals &GetPlayerVitals();

	void Start_Sprint();
	void Stop_Sprint();

#pragma endregion Public Functions
};

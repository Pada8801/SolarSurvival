// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SolarSurvival.h"
#include "SolarSurvival/Characters/PlayerCharacter/SolarSurvivalCharacter.h"
#include "../SolarSurvival/Items/Ammo/BaseProjectile/SolarSurvivalProjectile.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Hearing.h"
#include "ThirdParty/sqlite/sqlite/sqlite3.h"


//ability things
#include "SolarSurvival/Components/AbilityComponent/SolarAbilitySystemComponent.h"
#include "SolarSurvival/Abilitys/Stats/Character/UCharacterAttributeSet.h"
#include "Abilities/GameplayAbility_CharacterJump.h"

#if WITH_SERVER_CODE
#include "../SolarSurvivalServer/SolarSurvivalServer.h"
#endif

//////////////////////////////////////////////////////////////////////////
// ASolarSurvivalCharacter

FVitals::FVitals()
{
	fCurrentHP = 1500.0f;
	fMaxHP = 1500.0f;

	fCurrentStamina = 1500.0f;
	fMaxStamina = 1500.0f;

	fCurrentHunger = 1500.0f;
	fMaxHunger = 1500.0f;

	fCurrentThirst = 1500.0f;
	fMaxThirst = 1500.0f;

	fCurrentSanity = 1500.0f;
	fMaxSanity = 1500.0f;
}

void FVitals::ModifyHP(float fModHP)
{
	fCurrentHP += fModHP;
	if (fCurrentHP > fMaxHP)
	{
		fCurrentHP = fMaxHP;
	}
	if (fCurrentHP < 0)
	{
		fCurrentHP = 0;
	}
}

ASolarSurvivalCharacter::ASolarSurvivalCharacter(const class FObjectInitializer& FOI)
	: Super(FOI)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	//FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	//FirstPersonCameraComponent->AttachSocketName("Cammera socket");
	//FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	CharacterMesh = FOI.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh"));
	//Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//CharacterMesh->AttachParent = GetCapsuleComponent();

	CharacterMesh->SetupAttachment(GetCapsuleComponent());
	CharacterMesh->RelativeLocation = FVector(0.f, 0.f, -150.f);
	CharacterMesh->bCastDynamicShadow = false;
	CharacterMesh->CastShadow = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Hearing::StaticClass(), this);


	abilityComponent = FOI.CreateDefaultSubobject<USolarAbilitySystemComponent>(this, TEXT("CharacterAbilityComponent"));
	abilityComponent->SetIsReplicated(true);

}

void ASolarSurvivalCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetAbilitySystemComponent()->InitStats(UCharacterAttributeSet::StaticClass(), NULL);
}


//////////////////////////////////////////////////////////////////////////
// Input

void ASolarSurvivalCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ASolarSurvivalCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ASolarSurvivalCharacter::LookUpAtRate);
	InputComponent->BindAxis("MoveForward", this, &ASolarSurvivalCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASolarSurvivalCharacter::MoveRight);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASolarSurvivalCharacter::TouchStarted);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ASolarSurvivalCharacter::OnFire);
	InputComponent->BindAction("Debug", IE_Pressed, this, &ASolarSurvivalCharacter::Debug);
	//InputComponent->BindKey(EKeys::P, IE_Pressed, this, &ASolarSurvivalCharacter::Debug); example how to dynamicly bind to a key in c++
	InputComponent->BindAction("Interact", IE_Pressed, this, &ASolarSurvivalCharacter::Interact);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ASolarSurvivalCharacter::Start_Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ASolarSurvivalCharacter::Stop_Sprint);
}

void ASolarSurvivalCharacter::OnFire()
{
	ServerOnFire();
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);

		}
	}
}

void ASolarSurvivalCharacter::Debug()
{
	GetPlayerVitals().fCurrentHP = GetPlayerVitals().fCurrentHP + 300.0f;
	//GetPlayerVitals().ModifyHP(GetPlayerVitals().fCurrentHP + 500);
}

void ASolarSurvivalCharacter::Interact()
{
	if (Role != ROLE_Authority)
	{
		// we are not the server, so lets send an RPC to request to interact with the object
		Server_Interact();
	}
	if (Role == ROLE_Authority)
	{
		//ASolarSurvivalCharacter *pcharacter;
	//	if (pcharacter)
	//	{
	//		pcharacter->interactiveComponent->Use(this);
	//	}
	}
	// handle interaction here
}

bool ASolarSurvivalCharacter::Server_Interact_Validate()
{
	return true;
}

void ASolarSurvivalCharacter::Server_Interact_Implementation()
{
	if (HasAuthority())
	{
		Interact();
	}
}

void ASolarSurvivalCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

void ASolarSurvivalCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASolarSurvivalCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASolarSurvivalCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASolarSurvivalCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASolarSurvivalCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Role == ROLE_Authority)
	{
		DoSanityChecks();
		// this if case is currently just a testing way to slowly decrease hp for simple checking, this will be removed
		if (GetPlayerVitals().fCurrentHP > 0)
		{
			GetPlayerVitals().fCurrentHP = GetPlayerVitals().fCurrentHP - 0.5f;
		}
	}
	if (IsLocallyControlled() &&  Role < ROLE_Authority)
	{
		if (GetPlayerVitals().fCurrentHP <= 0)
		{
			const auto pWorld = GetWorld();
			FVector testVector = FVector(0, 0, 0);
			FString testString = "You are DEAD!";
			DrawDebugString(pWorld, testVector, testString, NULL, FColor::Red, 1.0f);
		}
	}
	//UAIPerceptionSystem
}

void ASolarSurvivalCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASolarSurvivalCharacter, characterVitals, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASolarSurvivalCharacter, abilityComponent, COND_OwnerOnly);
}

bool ASolarSurvivalCharacter::ServerOnFire_Validate()
{
	return true;
}

void ASolarSurvivalCharacter::ServerOnFire_Implementation()
{
	if (Role == ROLE_Authority)
	{
		GetPlayerVitals().fCurrentHP = GetPlayerVitals().fCurrentHP + 100.0f;
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			const auto World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile at the muzzle
				World->SpawnActor<ASolarSurvivalProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				MakeNoise(1.0f);
			}
		}
	}
}

void ASolarSurvivalCharacter::DoSanityChecks()
{
	if (GetPlayerVitals().fCurrentHP < 0)
	{
		GetPlayerVitals().fCurrentHP = 0;
	}
	if (GetPlayerVitals().fCurrentHP > GetPlayerVitals().fMaxHP)
	{
		GetPlayerVitals().fCurrentHP = GetPlayerVitals().fMaxHP;
		UE_LOG(LogTemp, Warning, TEXT("Current HP is Over max hp, setting to max hp! Current hp is now %f"), GetPlayerVitals().fCurrentHP);
	}
}

USurvivalInteractive *ASolarSurvivalCharacter::GetInteractionComponent()
{
	if (interactiveComponent)
	{
		return interactiveComponent;
	}
	else
	{
		return nullptr;
	}
}

FVitals &ASolarSurvivalCharacter::GetPlayerVitals()
{
	return characterVitals;
}

void ASolarSurvivalCharacter::Start_Sprint()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed Sprint"));
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Sprint pressed");
}

void ASolarSurvivalCharacter::Stop_Sprint()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Sprint released");


 	FVector testVector = FVector(0, 0, 0);
	FString testString = FString::SanitizeFloat(GetAbilitySystemComponent()->GetCharacterAttributes()->Health);
 	DrawDebugString(GetWorld(), testVector, testString, NULL, FColor::Red, 1.0f);

}

USolarAbilitySystemComponent* ASolarSurvivalCharacter::GetAbilitySystemComponent()
{ 
	return abilityComponent;
}



// bool ASolarSurvivalCharacter::ReplicateSubobjects(UActorChannel* channel, FOutBunch* bunch, FReplicationFlags* repFlags) 
// {
// 	check(channel && bunch && repFlags);
// 
// 	bool wroteSomething = Super::ReplicateSubobjects(channel, bunch, repFlags);
// 
// 	//wroteSomething |= channel->ReplicateSubobject(MyAwesomeItem, *bunch, *repFlags);
// 	return wroteSomething;
// }
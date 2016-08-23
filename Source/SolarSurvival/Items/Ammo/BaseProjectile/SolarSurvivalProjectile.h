// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "SolarSurvivalProjectile.generated.h"

UCLASS(config = Game)
class ASolarSurvivalProjectile : public AActor
{
public:
	GENERATED_BODY()

	ASolarSurvivalProjectile(const FObjectInitializer&);

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent *CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	UProjectileMovementComponent *ProjectileMovement;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

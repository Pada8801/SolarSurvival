

#pragma once

#include "Components/ActorComponent.h"
#include "SurvivalInteractive.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = SolarSurvival, meta = (BlueprintSpawnableComponent))
class SOLARSURVIVAL_API USurvivalInteractive : public UActorComponent
{
	GENERATED_BODY()
private:
protected:
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InteractionSettings)
	USphereComponent *interactionCollisionSphere;

	USurvivalInteractive(const class FObjectInitializer&);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};

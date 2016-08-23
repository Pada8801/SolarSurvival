

#include "SolarSurvival.h"
#include "SurvivalInteractive.h"


USurvivalInteractive::USurvivalInteractive(const class FObjectInitializer& FOI)
	: Super(FOI)
{
	PrimaryComponentTick.bCanEverTick = true;

	interactionCollisionSphere = FOI.CreateDefaultSubobject<USphereComponent>(this, TEXT("InteractionColision"));
	interactionCollisionSphere->InitSphereRadius(2.0f);
	//interactionCollisionSphere->BodyInstance.SetCollisionProfileName("InteractionCheck");
}

void USurvivalInteractive::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
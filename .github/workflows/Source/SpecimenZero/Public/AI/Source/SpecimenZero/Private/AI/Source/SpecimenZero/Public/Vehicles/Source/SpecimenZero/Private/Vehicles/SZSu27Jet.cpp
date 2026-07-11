#include "Vehicles/SZSu27Jet.h"
#include "Components/StaticMeshComponent.h"

ASZSu27Jet::ASZSu27Jet()
{
    PrimaryActorTick.bCanEverTick = true;
    // Set low tick rate for non-essential flight updates to save mobile CPU
    PrimaryActorTick.TickInterval = 0.01f; 
}

void ASZSu27Jet::UpdateFlightPhysics(float DeltaTime)
{
    if (bIsCobraActive)
    {
        // During Cobra, we bleed speed and increase pitch dramatically
        FVector CobraForce = GetActorForwardVector() * (FlightSpeed * 0.2f);
        Cast<UStaticMeshComponent>(GetRootComponent())->AddForce(CobraForce);
        
        CobraTimer += DeltaTime;
        if (CobraTimer >= MaxCobraTime) bIsCobraActive = false;
    }
    else
    {
        FVector StandardForce = GetActorForwardVector() * FlightSpeed;
        Cast<UStaticMeshComponent>(GetRootComponent())->AddForce(StandardForce);
    }
}

void ASZSu27Jet::ExecuteCobraManeuver()
{
    if (!bIsCobraActive)
    {
        bIsCobraActive = true;
        CobraTimer = 0.0f;
        
        // Apply immediate angular impulse for the "Cobra" look
        FVector PitchTorque = GetActorRightVector() * -CobraPitchStrength;
        Cast<UStaticMeshComponent>(GetRootComponent())->AddAngularImpulseInDegrees(PitchTorque, NAME_None, true);
    }
}

void ASZSu27Jet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateFlightPhysics(DeltaTime);
}

#include "Weapon/SZHomingMissile.h"

ASZHomingMissile::ASZHomingMissile()
{
    // Enable Homing logic built into UE5 Projectile Movement
    ProjectileMovement->bIsHomingProjectile = true;
    ProjectileMovement->HomingAccelerationMagnitude = 20000.f;
}

void ASZHomingMissile::SetMissileTarget(AActor* NewTarget)
{
    if (NewTarget && ProjectileMovement)
    {
        ProjectileMovement->HomingTargetComponent = NewTarget->GetRootComponent();
    }
}

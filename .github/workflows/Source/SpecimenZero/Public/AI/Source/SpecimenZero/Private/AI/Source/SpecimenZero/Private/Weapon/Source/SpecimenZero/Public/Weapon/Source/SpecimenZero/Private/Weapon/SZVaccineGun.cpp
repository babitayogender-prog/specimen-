#include "Weapon/SZVaccineGun.h"
#include "Weapon/SZProjectile.h"

ASZVaccineGun::ASZVaccineGun() {}

void ASZVaccineGun::FireVaccine(FVector MuzzleLocation, FRotator MuzzleRotation)
{
    if (VaccineProjectileClass && GetWorld())
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        GetWorld()->SpawnActor<ASZProjectile>(VaccineProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    }
}

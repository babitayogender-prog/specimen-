#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SZVaccineGun.generated.h"

UCLASS()
class SPECIMENZERO_API ASZVaccineGun : public AActor
{
    GENERATED_BODY()

public:
    ASZVaccineGun();

    // The cure projectile (Set in Blueprint)
    UPROPERTY(EditAnywhere, Category = "Weapon")
    TSubclassOf<class ASZProjectile> VaccineProjectileClass;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void FireVaccine(FVector MuzzleLocation, FRotator MuzzleRotation);
};

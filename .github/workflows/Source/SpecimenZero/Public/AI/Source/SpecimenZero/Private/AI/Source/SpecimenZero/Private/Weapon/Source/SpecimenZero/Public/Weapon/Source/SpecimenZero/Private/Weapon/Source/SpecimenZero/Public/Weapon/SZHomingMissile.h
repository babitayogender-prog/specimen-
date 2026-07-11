#pragma once

#include "CoreMinimal.h"
#include "Weapon/SZProjectile.h"
#include "SZHomingMissile.generated.h"

UCLASS()
class SPECIMENZERO_API ASZHomingMissile : public ASZProjectile
{
    GENERATED_BODY()

public:
    ASZHomingMissile();

    // Set target for the missile to follow
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void SetMissileTarget(AActor* NewTarget);
};

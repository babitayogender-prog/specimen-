#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SZProjectile.generated.h"

UCLASS()
class SPECIMENZERO_API ASZProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASZProjectile();

    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    USphereComponent* CollisionComp;

protected:
    // Performance: Projectiles destroy themselves after a few seconds to save RAM
    UPROPERTY(EditAnywhere, Category = "Stats")
    float Lifespan = 3.0f;

    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
```

### File 12: `SZProjectile.cpp`
**Location:** `/Source/SpecimenZero/Private/Weapon/SZProjectile.cpp`

```cpp
#include "Weapon/SZProjectile.h"

ASZProjectile::ASZProjectile()
{
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->SetCollisionProfileName("Projectile");
    RootComponent = CollisionComp;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    
    // Optimization: Disable expensive bounce physics for mobile
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = Lifespan;
}

void ASZProjectile::BeginPlay()
{
    Super::BeginPlay();
    CollisionComp->OnComponentHit.AddDynamic(this, &ASZProjectile::OnHit);
}

void ASZProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Base implementation: Eliminate self on impact
    Destroy();
}
```

---

### File 13: `SZVaccineGun.h` (The Mission Tool)
**Location:** `/Source/SpecimenZero/Public/Weapon/SZVaccineGun.h`
*Handles the logic for curing Patient Zero.*

```cpp
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

    // The cure projectile class (Assigned in Blueprint)
    UPROPERTY(EditAnywhere, Category = "Weapon")
    TSubclassOf<class ASZProjectile> VaccineProjectileClass;

    UFUNCTION(BlueprintCallable, Category = "Action")
    void FireVaccine(FVector MuzzleLocation, FRotator MuzzleRotation);
};
```

### File 14: `SZVaccineGun.cpp`
**Location:** `/Source/SpecimenZero/Private/Weapon/SZVaccineGun.cpp`

```cpp
#include "Weapon/SZVaccineGun.h"
#include "Weapon/SZProjectile.h"
#include "Engine/World.h"

ASZVaccineGun::ASZVaccineGun() {}

void ASZVaccineGun::FireVaccine(FVector MuzzleLocation, FRotator MuzzleRotation)
{
    if (VaccineProjectileClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        GetWorld()->SpawnActor<ASZProjectile>(VaccineProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    }
}
```

---

### File 15: `SZHomingMissile.h` (Su-27 Armament)
**Location:** `/Source/SpecimenZero/Public/Weapon/SZHomingMissile.h`
*Mobile-optimized homing logic for aircraft.*

```cpp
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

    // Sets the target for the missile to follow
    void SetMissileTarget(AActor* NewTarget);

protected:
    virtual void BeginPlay() override;
};
```

### File 16: `SZHomingMissile.cpp`
**Location:** `/Source/SpecimenZero/Private/Weapon/SZHomingMissile.cpp`

```cpp
#include "Weapon/SZHomingMissile.h"

ASZHomingMissile::ASZHomingMissile()
{
    // Homing Setup
    ProjectileMovement->bIsHomingProjectile = true;
    ProjectileMovement->HomingAccelerationMagnitude = 15000.f;
}

void ASZHomingMissile::BeginPlay()
{
    Super::BeginPlay();
}

void ASZHomingMissile::SetMissileTarget(AActor* NewTarget)
{
    if (NewTarget && ProjectileMovement)
    {
        // Target's scene component is required for the homing logic
        ProjectileMovement->HomingTargetComponent = NewTarget->GetRootComponent();
    }
}
```

### Why this is stable for Small Phones:
1.  **Low LifeSpan:** Projectiles exist for only 3 seconds. This prevents "Actor Bloat" where hundreds of hidden bullets eat up your 4GB RAM.
2.  **No Bounces:** Calculating physics reflections is CPU-heavy. We `Destroy()` on hit to keep the framerate high.
3.  **Chaos Optimization:** By using `USphereComponent` with a tiny radius (5.0f), the physics engine (Chaos) performs very fast collision checks.

**When you are ready, say "Next" and I will provide the Mobile HUD UI (Touch Joysticks) and the final Android packaging configuration for the App Store/GitHub Release.**

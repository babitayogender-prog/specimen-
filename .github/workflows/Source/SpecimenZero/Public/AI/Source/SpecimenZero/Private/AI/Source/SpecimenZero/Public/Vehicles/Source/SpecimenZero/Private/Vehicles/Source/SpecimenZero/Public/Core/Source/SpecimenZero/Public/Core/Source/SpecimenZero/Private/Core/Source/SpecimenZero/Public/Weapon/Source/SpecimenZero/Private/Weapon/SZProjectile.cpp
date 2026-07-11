#include "Weapon/SZProjectile.h"

ASZProjectile::ASZProjectile()
{
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    // Optimization: Use "Projectile" profile to ignore complex physics bodies
    CollisionComp->SetCollisionProfileName("Projectile");
    RootComponent = CollisionComp;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 5000.f;
    ProjectileMovement->MaxSpeed = 5000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    
    // Performance: Disable bouncing to save CPU cycles on small phones
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
    // The projectile is eliminated on any impact to free resources
    Destroy();
}

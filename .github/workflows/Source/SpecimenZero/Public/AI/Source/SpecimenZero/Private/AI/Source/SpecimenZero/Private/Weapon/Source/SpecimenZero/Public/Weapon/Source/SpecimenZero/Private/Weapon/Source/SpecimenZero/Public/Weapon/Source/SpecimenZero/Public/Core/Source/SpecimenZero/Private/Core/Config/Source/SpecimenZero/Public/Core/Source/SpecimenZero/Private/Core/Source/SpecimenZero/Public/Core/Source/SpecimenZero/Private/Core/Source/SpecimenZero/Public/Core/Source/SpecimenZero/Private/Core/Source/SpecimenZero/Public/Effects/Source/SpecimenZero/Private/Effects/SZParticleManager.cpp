#include "Effects/SZParticleManager.h"
#include "NiagaraSystem.h"

void USZParticleManager::PlayOptimizedEffect(UNiagaraSystem* EffectAsset, FVector Location, FRotator Rotation)
{
    if (!EffectAsset) return;

    // ENiagaraPoolingMethod::AutoRelease ensures the component returns to the pool 
    // instead of being Garbage Collected, which is the #1 cause of mobile "Hanging".
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), 
        EffectAsset, 
        Location, 
        Rotation, 
        FVector(1.f), 
        true, 
        true, 
        DefaultPooling,
        true
    );
}

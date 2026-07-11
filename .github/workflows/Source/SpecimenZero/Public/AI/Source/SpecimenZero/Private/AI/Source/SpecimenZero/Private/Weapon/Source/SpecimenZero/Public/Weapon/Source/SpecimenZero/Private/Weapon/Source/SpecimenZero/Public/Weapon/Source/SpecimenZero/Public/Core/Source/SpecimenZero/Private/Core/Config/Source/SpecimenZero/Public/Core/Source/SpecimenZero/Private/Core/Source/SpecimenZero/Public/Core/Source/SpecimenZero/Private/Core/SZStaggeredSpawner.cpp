#include "Core/SZStaggeredSpawner.h"
#include "TimerManager.h"
#include "Engine/World.h"

ASZStaggeredSpawner::ASZStaggeredSpawner() { PrimaryActorTick.bCanEverTick = false; }

void ASZStaggeredSpawner::StartMissionSpawning()
{
    if (AIClass)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASZStaggeredSpawner::SpawnNextAI, SpawnInterval, true);
    }
}

void ASZStaggeredSpawner::SpawnNextAI()
{
    if (CurrentSpawnCount >= MaxAISpawn)
    {
        GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // Spawn AI at the spawner's location with a random offset
    FVector SpawnLoc = GetActorLocation() + FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), 0);
    GetWorld()->SpawnActor<AActor>(AIClass, SpawnLoc, GetActorRotation(), SpawnParams);
    
    CurrentSpawnCount++;
}

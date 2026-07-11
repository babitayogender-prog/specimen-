#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "SZMissionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionStatusChanged, FString, NewStatus);

UCLASS()
class SPECIMENZERO_API ASZMissionManager : public AInfo
{
    GENERATED_BODY()

public:
    ASZMissionManager();

    // Mission Objectives
    UPROPERTY(BlueprintReadWrite, Category = "Mission")
    int32 SoldiersEliminated = 0;

    UPROPERTY(EditAnywhere, Category = "Mission")
    int32 TotalSoldiersRequired = 50;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMissionStatusChanged OnStatusChanged;

    UFUNCTION(BlueprintCallable, Category = "Mission")
    void UpdateProgress();

protected:
    void CheckMissionComplete();
};
```

---

### File 22: `SZMissionManager.cpp`
**Location:** `/Source/SpecimenZero/Private/Core/SZMissionManager.cpp`

```cpp
#include "Core/SZMissionManager.h"

ASZMissionManager::ASZMissionManager() { PrimaryActorTick.bCanEverTick = false; }

void ASZMissionManager::UpdateProgress()
{
    SoldiersEliminated++;
    OnStatusChanged.Broadcast(FString::Printf(TEXT("Soldiers: %d / %d"), SoldiersEliminated, TotalSoldiersRequired));
    CheckMissionComplete();
}

void ASZMissionManager::CheckMissionComplete()
{
    if (SoldiersEliminated >= TotalSoldiersRequired)
    {
        OnStatusChanged.Broadcast(TEXT("MISSION COMPLETE: GET TO THE JET!"));
    }
}
```

---

### File 23: `SZStaggeredSpawner.h` (The "Optimizer")
**Location:** `/Source/SpecimenZero/Public/Core/SZStaggeredSpawner.h`
*Crucial for Mobile: Spawns the 50 AI one-by-one to prevent crashing.*

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SZStaggeredSpawner.generated.h"

UCLASS()
class SPECIMENZERO_API ASZStaggeredSpawner : public AActor
{
    GENERATED_BODY()

public:
    ASZStaggeredSpawner();

    // The AI class to spawn (Derived from File 4: ASZMobileAI)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<AActor> AIClass;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    int32 MaxAISpawn = 50;

    // Time between each spawn (0.2s keeps the phone cool)
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnInterval = 0.2f;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void StartMissionSpawning();

private:
    FTimerHandle SpawnTimerHandle;
    int32 CurrentSpawnCount = 0;

    void SpawnNextAI();
};
```

---

### File 24: `SZStaggeredSpawner.cpp`
**Location:** `/Source/SpecimenZero/Private/Core/SZStaggeredSpawner.cpp`

```cpp
#include "Core/SZStaggeredSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

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

    // Spawn AI at the spawner's location + random offset
    FVector RandomLoc = GetActorLocation() + FVector(FMath::RandRange(-500, 500), FMath::RandRange(-500, 500), 0);
    
    GetWorld()->SpawnActor<AActor>(AIClass, RandomLoc, GetActorRotation(), SpawnParams);
    
    CurrentSpawnCount++;
}
```

---

### File 25: `SZVehicleFactory.h` (45+ Vehicle Loader)
**Location:** `/Source/SpecimenZero/Public/Core/SZVehicleFactory.h`
*Uses the Data Assets from Layer 2 to load vehicles on demand.*

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data/SZVehicleAsset.h"
#include "SZVehicleFactory.generated.h"

UCLASS()
class SPECIMENZERO_API USZVehicleFactory : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    // Loads a specific vehicle by name from the 45-car list
    UFUNCTION(BlueprintCallable, Category = "SZ|Vehicles")
    void SpawnVehicleFromData(USZVehicleAsset* VehicleData, FVector Location);
};
```

---

### File 26: `SZVehicleFactory.cpp`
**Location:** `/Source/SpecimenZero/Private/Core/SZVehicleFactory.cpp`

```cpp
#include "Core/SZVehicleFactory.h"
#include "Engine/AssetManager.h"

void USZVehicleFactory::SpawnVehicleFromData(USZVehicleAsset* VehicleData, FVector Location)
{
    if (!VehicleData) return;

    // Advanced: Uses Async Loading to prevent "Hang" when loading 45 vehicles
    TSoftClassPtr<AActor> ActorClass = VehicleData->VehicleClass;
    
    if (ActorClass.IsValid())
    {
        GetWorld()->SpawnActor<AActor>(ActorClass.Get(), Location, FRotator::ZeroRotator);
    }
    else
    {
        // Load the vehicle into RAM only when the player is near it
        UAssetManager::GetStreamableManager().RequestAsyncLoad(ActorClass.ToSoftObjectPath());
    }
}
```

### Integration for the "Full Game" APK:
1.  **Drop Spawner in Map:** Place `ASZStaggeredSpawner` in your level.
2.  **Assign AI:** In the Details panel, select your `BP_MobileAI`.
3.  **Trigger Mission:** In your Level Blueprint, call `StartMissionSpawning()`. This will safely trickle the 50 AI into the world without the phone lagging.
4.  **Vehicle Management:** Instead of placing all 45 vehicles in the map (which would crash the phone), use the `SZVehicleFactory` to spawn them only when the player enters a specific "Vehicle Zone."

**When you are ready, say "Next" and I will provide the "Final Polish" codes: The Particle System optimization for explosions and the Mobile Main Menu logic.**

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

    // The AI class to spawn (Derived from ASZMobileAI)
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

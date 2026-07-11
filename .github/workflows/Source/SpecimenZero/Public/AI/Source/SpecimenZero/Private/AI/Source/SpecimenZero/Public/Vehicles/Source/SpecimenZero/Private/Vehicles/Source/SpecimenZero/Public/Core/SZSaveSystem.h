#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SZSaveSystem.generated.h"

UCLASS()
class SPECIMENZERO_API USZSaveSystem : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    FVector LastPlayerLocation;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 MissionPhase = 1;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    bool bHasVaccine = false;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    FString SaveSlotName = TEXT("SpecimenZero_Slot0");
};

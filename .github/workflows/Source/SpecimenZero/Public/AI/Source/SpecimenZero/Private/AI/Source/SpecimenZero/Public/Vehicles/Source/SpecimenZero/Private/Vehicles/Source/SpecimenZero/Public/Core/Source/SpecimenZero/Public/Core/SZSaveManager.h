#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SZSaveSystem.h"
#include "SZSaveManager.generated.h"

UCLASS()
class SPECIMENZERO_API USZSaveManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // Called when clicking "Save and Leave"
    UFUNCTION(BlueprintCallable, Category = "SZ|Save")
    void SaveAndExit(FVector CurrentLocation, int32 CurrentPhase, bool bVaccineStatus);

    // Called when clicking "Continue" from Home Screen
    UFUNCTION(BlueprintCallable, Category = "SZ|Save")
    USZSaveSystem* LoadMissionProgress();

    // Called to eliminate old save data for "New Game"
    UFUNCTION(BlueprintCallable, Category = "SZ|Save")
    void ClearSaveData();
};

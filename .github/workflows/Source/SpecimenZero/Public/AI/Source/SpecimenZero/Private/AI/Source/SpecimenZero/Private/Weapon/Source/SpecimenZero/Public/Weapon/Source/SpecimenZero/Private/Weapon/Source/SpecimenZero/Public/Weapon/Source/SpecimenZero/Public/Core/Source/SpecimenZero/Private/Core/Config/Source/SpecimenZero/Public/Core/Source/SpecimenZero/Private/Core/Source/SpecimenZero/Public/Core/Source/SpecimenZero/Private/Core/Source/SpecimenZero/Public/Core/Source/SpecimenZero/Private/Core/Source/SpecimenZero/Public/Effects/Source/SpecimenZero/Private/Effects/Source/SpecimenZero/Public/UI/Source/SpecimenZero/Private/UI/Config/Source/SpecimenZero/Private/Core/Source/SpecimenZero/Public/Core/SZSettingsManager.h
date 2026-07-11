#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SZSettingsManager.generated.h"

UCLASS()
class SPECIMENZERO_API USZSettingsManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** 
     * Detects phone specs and applies 4K/2K/1K texture limits and Shadow quality.
     */
    UFUNCTION(BlueprintCallable, Category = "SZ|Settings")
    void AutoOptimizeForHardware();

    /** 
     * Handles the Android Hardware "Back" Button to open the Menu.
     */
    UFUNCTION(BlueprintCallable, Category = "SZ|Hardware")
    void HandleMobileBackAction();
};

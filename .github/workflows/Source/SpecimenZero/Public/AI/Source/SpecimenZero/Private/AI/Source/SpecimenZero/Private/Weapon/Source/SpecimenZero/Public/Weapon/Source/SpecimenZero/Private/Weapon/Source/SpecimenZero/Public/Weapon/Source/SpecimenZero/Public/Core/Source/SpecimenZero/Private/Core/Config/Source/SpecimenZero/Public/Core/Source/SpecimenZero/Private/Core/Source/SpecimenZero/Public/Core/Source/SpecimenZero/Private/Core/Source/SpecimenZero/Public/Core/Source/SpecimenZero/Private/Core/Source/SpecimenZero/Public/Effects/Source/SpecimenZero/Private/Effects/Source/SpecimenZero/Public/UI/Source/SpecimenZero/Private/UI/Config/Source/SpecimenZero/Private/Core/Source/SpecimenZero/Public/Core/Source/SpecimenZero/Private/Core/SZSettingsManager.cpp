#include "Core/SZSettingsManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameUserSettings.h"

void USZSettingsManager::AutoOptimizeForHardware()
{
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;

    // Detect Device Memory (Simplified logic for Mobile)
    int32 RAM_GB = FPlatformMemory::GetStats().TotalPhysicalGB;

    if (RAM_GB <= 4) // "Small" Phone
    {
        Settings->SetViewDistanceQuality(0);
        Settings->SetShadowQuality(0); // Shadows cause the most mobile hanging
        Settings->SetTextureQuality(1);
        UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("r.MobileContentScaleFactor 0.8"));
    }
    else // "Strong" Phone
    {
        Settings->SetViewDistanceQuality(2);
        Settings->SetShadowQuality(1);
        Settings->SetTextureQuality(2);
        UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("r.MobileContentScaleFactor 1.2"));
    }

    Settings->ApplySettings(false);
}

void USZSettingsManager::HandleMobileBackAction()
{
    // If player hits the hardware back button, we save and exit to menu
    // You can also use this to toggle the pause menu widget
    UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("input.ShowMenu"));
}

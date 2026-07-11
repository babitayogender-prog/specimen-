#include "Core/SZGameMode.h"
#include "Core/SZPlayerController.h"
#include "UI/SZMobileHUD.h"
#include "UObject/ConstructorHelpers.h"

ASZGameMode::ASZGameMode()
{
    // 1. Tell the game to use your C++ Player Controller
    PlayerControllerClass = ASZPlayerController::StaticClass();

    // 2. Assign the HUD (Wiring to the Blueprint we will create)
    static ConstructorHelpers::FClassFinder<AHUD> HUDBPClass(TEXT("/Game/UI/BP_MobileHUD"));
    if (HUDBPClass.Class != nullptr)
    {
        HUDClass = HUDBPClass.Class;
    }

    // 3. Set the Default Pawn (Your Main Character)
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BP_MainPlayer"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

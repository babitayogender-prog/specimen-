#include "UI/SZMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Core/SZSaveManager.h"
#include "Kismet/KismetSystemLibrary.h"

void USZMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Check if a save exists to show/hide the "Continue" button
    if (ContinueButton)
    {
        bool bSaveExists = UGameplayStatics::DoesSaveGameExist(TEXT("SpecimenZero_Slot0"), 0);
        ContinueButton->SetVisibility(bSaveExists ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void USZMainMenuWidget::StartNewGame()
{
    if (USZSaveManager* SaveMgr = GetGameInstance()->GetSubsystem<USZSaveManager>())
    {
        SaveMgr->ClearSaveData();
    }
    UGameplayStatics::OpenLevel(this, FName("L_MainMission"));
}

void USZMainMenuWidget::ContinueGame()
{
    UGameplayStatics::OpenLevel(this, FName("L_MainMission"));
}

void USZMainMenuWidget::QuitMobileApp()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

#include "Core/SZSaveManager.h"
#include "Kismet/GameplayStatics.h"

void USZSaveManager::SaveAndExit(FVector CurrentLocation, int32 CurrentPhase, bool bVaccineStatus)
{
    if (USZSaveSystem* SaveRef = Cast<USZSaveSystem>(UGameplayStatics::CreateSaveGameObject(USZSaveSystem::StaticClass())))
    {
        SaveRef->LastPlayerLocation = CurrentLocation;
        SaveRef->MissionPhase = CurrentPhase;
        SaveRef->bHasVaccine = bVaccineStatus;
        
        UGameplayStatics::SaveGameToSlot(SaveRef, TEXT("SpecimenZero_Slot0"), 0);
        
        // Mobile Exit Logic
        UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
    }
}

USZSaveSystem* USZSaveManager::LoadMissionProgress()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("SpecimenZero_Slot0"), 0))
    {
        return Cast<USZSaveSystem>(UGameplayStatics::LoadGameFromSlot(TEXT("SpecimenZero_Slot0"), 0));
    }
    return nullptr;
}

void USZSaveManager::ClearSaveData()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("SpecimenZero_Slot0"), 0))
    {
        UGameplayStatics::DeleteGameInSlot(TEXT("SpecimenZero_Slot0"), 0);
    }
}

#include "Core/SZMissionManager.h"

ASZMissionManager::ASZMissionManager() { PrimaryActorTick.bCanEverTick = false; }

void ASZMissionManager::UpdateProgress()
{
    SoldiersEliminated++;
    OnStatusChanged.Broadcast(FString::Printf(TEXT("Soldiers Eliminated: %d / %d"), SoldiersEliminated, TotalSoldiersRequired));
    CheckMissionComplete();
}

void ASZMissionManager::CheckMissionComplete()
{
    if (SoldiersEliminated >= TotalSoldiersRequired)
    {
        OnStatusChanged.Broadcast(TEXT("MISSION COMPLETE: REACH THE JET!"));
    }
}

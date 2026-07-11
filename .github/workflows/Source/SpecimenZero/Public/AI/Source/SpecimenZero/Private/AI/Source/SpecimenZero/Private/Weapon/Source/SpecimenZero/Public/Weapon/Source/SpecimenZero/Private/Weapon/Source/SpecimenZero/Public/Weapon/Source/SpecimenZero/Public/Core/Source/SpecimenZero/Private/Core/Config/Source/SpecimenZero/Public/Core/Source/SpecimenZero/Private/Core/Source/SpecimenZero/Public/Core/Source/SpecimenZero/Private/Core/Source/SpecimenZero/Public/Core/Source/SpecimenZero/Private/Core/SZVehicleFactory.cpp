#include "Core/SZVehicleFactory.h"
#include "Engine/AssetManager.h"

void USZVehicleFactory::RequestVehicleSpawn(USZVehicleAsset* Data, FVector Location)
{
    if (!Data) return;

    // Use Soft Class References to avoid loading all 45 vehicles into RAM at once
    TSoftClassPtr<AActor> VehicleClass = Data->VehicleClass;
    
    if (VehicleClass.IsValid())
    {
        GetWorld()->SpawnActor<AActor>(VehicleClass.Get(), Location, FRotator::ZeroRotator);
    }
    else
    {
        // Asynchronously load the vehicle if it's not in memory
        UAssetManager::GetStreamableManager().RequestAsyncLoad(VehicleClass.ToSoftObjectPath());
    }
}

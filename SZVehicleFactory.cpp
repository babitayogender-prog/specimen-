void USZVehicleFactory::RequestVehicleSpawn(USZVehicleAsset* Data, FVector Location)
{
    // 1. Check if another vehicle is already in RAM
    // 2. If so, eliminate the reference to the old vehicle to clear memory
    GEngine->ForceGarbageCollection(true); 

    TSoftClassPtr<AActor> VehicleClass = Data->VehicleClass;
    
    // 3. Load only the specific vehicle requested
    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
    Streamable.RequestAsyncLoad(VehicleClass.ToSoftObjectPath(), [this, VehicleClass, Location]()
    {
        GetWorld()->SpawnActor<AActor>(VehicleClass.Get(), Location, FRotator::ZeroRotator);
    });
}

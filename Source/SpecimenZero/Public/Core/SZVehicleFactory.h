#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Data/SZVehicleAsset.h"
#include "SZVehicleFactory.generated.h"

UCLASS()
class SPECIMENZERO_API USZVehicleFactory : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "SZ|Vehicles")
    void RequestVehicleSpawn(USZVehicleAsset* Data, FVector Location);
};

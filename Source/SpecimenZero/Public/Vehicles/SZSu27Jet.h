// SZSu27Jet.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SZSu27Jet.generated.h"

UCLASS()
class SPECIMENZERO_API ASZSu27Jet : public APawn
{
    GENERATED_BODY()

public:
    ASZSu27Jet();

    virtual void Tick(float DeltaTime) override;

    // Triggers the Pugachev's Cobra maneuver
    UFUNCTION(BlueprintCallable, Category = "Flight|Maneuver")
    void TriggerCobra();

protected:
    UPROPERTY(EditAnywhere, Category = "Flight")
    float Thrust = 5000.0f;

    UPROPERTY(EditAnywhere, Category = "Flight")
    float CobraPitchStrength = 1500.0f;

private:
    bool bIsPerformingCobra = false;
    float CobraTimer = 0.0f;
    float CobraDuration = 2.5f;

    void HandleFlightPhysics(float DeltaTime);
};

// SZSu27Jet.cpp
#include "SZSu27Jet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ASZSu27Jet::ASZSu27Jet()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASZSu27Jet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    HandleFlightPhysics(DeltaTime);

    if (bIsPerformingCobra)
    {
        CobraTimer += DeltaTime;
        if (CobraTimer >= CobraDuration)
        {
            bIsPerformingCobra = false;
            CobraTimer = 0.0f;
        }
    }
}

void ASZSu27Jet::TriggerCobra()
{
    if (!bIsPerformingCobra)
    {
        bIsPerformingCobra = true;
        // Apply massive upward pitch impulse for the Cobra look
        FVector CobraTorque = GetActorRightVector() * -CobraPitchStrength;
        Cast<UStaticMeshComponent>(GetRootComponent())->AddAngularImpulseInDegrees(CobraTorque, NAME_None, true);
    }
}

void ASZSu27Jet::HandleFlightPhysics(float DeltaTime)
{
    // Simplified mobile flight: Add forward force
    FVector ForwardForce = GetActorForwardVector() * Thrust;
    Cast<UStaticMeshComponent>(GetRootComponent())->AddForce(ForwardForce);
}

// SZSaveGame.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SZSaveGame.generated.h"

UCLASS()
class SPECIMENZERO_API USZSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FVector LastPlayerLocation;

    UPROPERTY()
    int32 CurrentMissionPhase = 1;

    UPROPERTY()
    bool bHasVaccine = false;

    UPROPERTY()
    FString SaveSlotName = TEXT("MobileSaveSlot");
};

// SZSaveManager.h
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SZSaveManager.generated.h"

UCLASS()
class SPECIMENZERO_API USZSaveManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "SZ|SaveSystem")
    void SaveGameData(FVector Location, int32 Phase, bool bVaccine);

    UFUNCTION(BlueprintCallable, Category = "SZ|SaveSystem")
    class USZSaveGame* LoadGameData();
};

// SZSaveManager.cpp
#include "SZSaveManager.h"
#include "SZSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USZSaveManager::SaveGameData(FVector Location, int32 Phase, bool bVaccine)
{
    if (USZSaveGame* SaveInstance = Cast<USZSaveGame>(UGameplayStatics::CreateSaveGameObject(USZSaveGame::StaticClass())))
    {
        SaveInstance->LastPlayerLocation = Location;
        SaveInstance->CurrentMissionPhase = Phase;
        SaveInstance->bHasVaccine = bVaccine;
        UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->SaveSlotName, 0);
    }
}

USZSaveGame* USZSaveManager::LoadGameData()
{
    return Cast<USZSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MobileSaveSlot"), 0));
}

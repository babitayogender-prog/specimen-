#include "Core/SZAudioManager.h"
#include "Kismet/GameplayStatics.h"

void USZAudioManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // Create a concurrency rule: Never more than 12 sounds at once on mobile
    GlobalMobileConcurrency = NewObject<USoundConcurrency>(this);
    GlobalMobileConcurrency->Config.MaxCount = 12;
    GlobalMobileConcurrency->Config.ResolutionRule = EMaxSoundReachedAction::StopOldest;
}

void USZAudioManager::PlayLimitedSound(USoundBase* Sound, FVector Location)
{
    if (!Sound) return;

    FForceFeedbackParameters FFParams;
    UGameplayStatics::PlaySoundAtLocation(
        GetWorld(), 
        Sound, 
        Location, 
        1.f, 1.f, 0.f, 
        nullptr, 
        GlobalMobileConcurrency
    );
}

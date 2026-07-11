#include "Core/SZPlayerController.h"
#include "EnhancedInputSubsystems.h"

void ASZPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Enable Touch Events for APK
	bShowMouseCursor = false;
	bEnableTouchEvents = true;
	bEnableTouchOverEvents = true;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MobileInputMapping)
		{
			Subsystem->AddMappingContext(MobileInputMapping, 0);
		}
	}
}

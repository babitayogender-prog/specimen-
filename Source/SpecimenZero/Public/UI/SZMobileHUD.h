#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SZMobileHUD.generated.h"

UCLASS()
class SPECIMENZERO_API USZMobileHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	// Executes 'Cobra' on the current Su-27
	UFUNCTION(BlueprintCallable, Category = "SZ|Input")
	void TriggerCobraAction();

	// Logic to Save and Eliminate the session
	UFUNCTION(BlueprintCallable, Category = "SZ|Mission")
	void SaveAndQuitToMobileHome();
};

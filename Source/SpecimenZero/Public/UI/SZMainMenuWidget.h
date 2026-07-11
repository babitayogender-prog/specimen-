#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SZMainMenuWidget.generated.h"

UCLASS()
class SPECIMENZERO_API USZMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    // The UI Button for "Continue" (Bind in BP)
    UPROPERTY(meta = (BindWidgetOptional))
    class UButton* ContinueButton;

    UFUNCTION(BlueprintCallable, Category = "SZ|UI")
    void StartNewGame();

    UFUNCTION(BlueprintCallable, Category = "SZ|UI")
    void ContinueGame();

    UFUNCTION(BlueprintCallable, Category = "SZ|UI")
    void QuitMobileApp();
};

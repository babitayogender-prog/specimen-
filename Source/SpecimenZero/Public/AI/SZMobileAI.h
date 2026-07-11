#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SZMobileAI.generated.h"

UCLASS()
class SPECIMENZERO_API ASZMobileAI : public ACharacter
{
	GENERATED_BODY()

public:
	ASZMobileAI();

protected:
	virtual void BeginPlay() override;

	// Optimization: Logic runs every 0.1s instead of every frame to prevent hanging
	UPROPERTY(EditAnywhere, Category = "SZ|Optimization")
	float MobileTickRate = 0.1f;
};

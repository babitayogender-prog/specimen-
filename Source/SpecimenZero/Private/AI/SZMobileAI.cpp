#include "AI/SZMobileAI.h"
#include "Components/SkeletalMeshComponent.h"

ASZMobileAI::ASZMobileAI()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = MobileTickRate;
}

void ASZMobileAI::BeginPlay()
{
	Super::BeginPlay();
	
	// Force Low-Poly LOD to save GPU RAM on small devices
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetForcedLOD(2);
	}
}

// Move 36 Studio

#include "Environment/ToggleSwitch.h"
#include "Components/SwitchComponent.h"
#include "Components/StaticMeshComponent.h"

AToggleSwitch::AToggleSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = RootMesh;
	SwitchComponent = CreateDefaultSubobject<USwitchComponent>(TEXT("Switch"));
}

void AToggleSwitch::Use(AActor* UserActor)
{
	bool const NewValue = SwitchComponent->ToggleValue();
}
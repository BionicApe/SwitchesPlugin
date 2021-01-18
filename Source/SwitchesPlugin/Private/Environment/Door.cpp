// // Created by Bionic Ape. All Rights Reserved.

#include "Environment/Door.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SwitchableComponent.h"

// Sets default values
ADoor::ADoor(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetMobility(EComponentMobility::Static);
	RootComponent = Frame;

	BlockingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockingMesh"));
	BlockingMesh->SetupAttachment(RootComponent);
	BlockingMesh->SetRelativeScale3D(FVector(0.5f, 4.983398f, 4.527499f));

	SwitchableComponent = CreateDefaultSubobject<USwitchableComponent>(TEXT("SwitchableComponent"));
	SwitchableComponent->OnResultChange.AddDynamic(this, &ADoor::OnSwitchableResultChanged);
	SwitchableComponent->bNoSwitchsDefaultValue = false;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::SetOpenDoor(bool NewValue)
{
	BlockingMesh->SetVisibility(!NewValue);
	BlockingMesh->SetCollisionEnabled(NewValue ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryOnly);
}

void ADoor::OpenDoor()
{
	SetOpenDoor(true);
}

void ADoor::CloseDoor()
{
	SetOpenDoor(false);
}

void ADoor::OnSwitchableResultChanged(bool NewValue)
{
	SetOpenDoor(NewValue);
}
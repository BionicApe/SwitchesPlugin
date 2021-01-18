// Created by Bionic Ape. All rights reseved.

#include "Environment/SwitchableActor.h"
#include "Components/SwitchableComponent.h"

// Sets default values
ASwitchableActor::ASwitchableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwitchableComponent = CreateDefaultSubobject<USwitchableComponent>(TEXT("SwitchableComponent"));
}
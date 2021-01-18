// Created by Bionic Ape. All rights reseved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchableActor.generated.h"

class USwitchableComponent;

UCLASS()
class SWITCHESPLUGIN_API ASwitchableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Switches")
	USwitchableComponent* SwitchableComponent;
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Get the Switchable Component"), Category = "Switches")
	USwitchableComponent* GetSwitchableComponent() { return SwitchableComponent; }

public:

	ASwitchableActor();

};

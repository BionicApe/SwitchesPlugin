// // Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToggleSwitch.generated.h"


class UStaticMeshComponent;
class USwitchComponent;


UCLASS()
class SWITCHESPLUGIN_API AToggleSwitch : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	UStaticMeshComponent* RootMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Switches")
	USwitchComponent* SwitchComponent;
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Get the Disturbable Component"), Category = "Switches")
	USwitchComponent* GetSwitch() const { return SwitchComponent; }

	AToggleSwitch();

	UFUNCTION(BlueprintCallable, Category = Switches)
	void Use(AActor* UserActor);
};

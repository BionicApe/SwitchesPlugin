// // Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class USwitchableComponent;

UCLASS()
class SWITCHESPLUGIN_API ADoor : public AActor/*, public ISavable*/
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	UStaticMeshComponent* Frame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Mesh")
	UStaticMeshComponent* BlockingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Switches")
	USwitchableComponent* SwitchableComponent;
	UFUNCTION(BlueprintCallable, meta = (Tooltip = "Get the Switchable Component"), Category = "Switches")
	USwitchableComponent* GetSwitchableComponent() { return SwitchableComponent; }

protected:

	virtual void BeginPlay() override;

public:

	ADoor(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnSwitchableResultChanged(bool NewValue);

	UFUNCTION(BlueprintCallable, Category = Switches)
	void SetOpenDoor(bool Value);

	void OpenDoor();

	void CloseDoor();
};

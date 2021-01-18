// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwitchableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchableResultChanged, const bool, Value);

class USwitchComponent;
class USaveGameHelper;

UENUM(BlueprintType)
enum class ESwitchableCalculationType : uint8
{
	OR	UMETA(DisplayName = "OR"),
	AND	UMETA(DisplayName = "AND")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWITCHESPLUGIN_API USwitchableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/** Last value of is ActivatedCache, so we can notify if there's a change */
	
	UPROPERTY()
	bool bIsActivatedCache;
	
public:


	/** Default value when there's no Switch Component*/
	UPROPERTY(EditAnywhere, Category = Switches)
	bool bNoSwitchsDefaultValue = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Switches)
	TArray<USwitchComponent*> SwitchComponents;

	UPROPERTY(EditAnywhere, Category = Switches)
	ESwitchableCalculationType CalculationType;

	UPROPERTY(BlueprintAssignable, Category = "Switches")
	FOnSwitchableResultChanged OnResultChange;

protected:
	//// Called when the game starts
	//virtual void BeginPlay() override;

	void CalculateIsSwitchableActived();

public:

	USwitchableComponent();

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual void AddSwitchComponent(USwitchComponent* NewSwitch);

	virtual void RemoveSwitchComponent(USwitchComponent* SwitchToRemove);

	virtual bool IsSwitchableActivated(bool bForceCalculate = true);

	UFUNCTION()
	virtual void OnSwitchValueChanged(bool NewValue);

	void RefreshIsActivatedCache(bool bForceBroadcast);
};

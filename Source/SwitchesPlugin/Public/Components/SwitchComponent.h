// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "SwitchComponent.generated.h"

class USwitchableComponent;
class ISwitchableInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchValueChanged,const bool, Value);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWITCHESPLUGIN_API USwitchComponent : public UActorComponent
{
	GENERATED_BODY()
public:

#if WITH_EDITOR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Switches)
	bool bEmptyArray;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Switches)
	AActor* AddSwitchableActor;
#endif // WITH_EDITOR

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Switches)
	bool bIsSwitchActive = false;

	UPROPERTY(BlueprintAssignable, Category = "Switches")
	FOnSwitchValueChanged OnValueChanged;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Switches)
	TArray<USwitchableComponent*> SwitchableComponents;
	
public:	

	USwitchComponent();

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif // WITH_EDITOR
	
	UFUNCTION(BlueprintCallable, Category = Switches)
	virtual bool ToggleValue();

	UFUNCTION(BlueprintCallable, Category = Switches)
	virtual bool IsSwitchActive() const { return bIsSwitchActive; }

	virtual void SetSwitchable(USwitchableComponent* NewSwitchable);

	UFUNCTION(BlueprintCallable, Category = Switches)
	virtual void SetSwitchValue(bool bNewValue);

	virtual void RemoveSwitchable(USwitchableComponent* SwitchableToDelete);

	virtual void RemoveSwitchables();
};
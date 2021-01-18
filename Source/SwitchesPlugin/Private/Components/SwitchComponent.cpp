// Created by Bionic Ape. All Rights Reserved.

#include "Components/SwitchComponent.h"
#include "Components/SwitchableComponent.h"

USwitchComponent::USwitchComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

#if WITH_EDITOR
void USwitchComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property &&PropertyChangedEvent.Property->GetName().Equals("AddSwitchableActor"))//Caution Property might be NULL
	{
		TGuardValue<bool> AutoRestore(GAllowActorScriptExecutionInEditor, true);
		USwitchableComponent* NewSwitchable = nullptr;
		if (AddSwitchableActor)
		{
			NewSwitchable = Cast<USwitchableComponent>(AddSwitchableActor->GetComponentByClass(USwitchableComponent::StaticClass()));
		}
		if (!NewSwitchable)
		{
			AddSwitchableActor = nullptr;
		}
		SetSwitchable(NewSwitchable);//Can be null on Purpose!
	}
	else if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName().Equals("bIsSwitchActive"))//Caution Property might be NULL
	{
		TGuardValue<bool> AutoRestore(GAllowActorScriptExecutionInEditor, true);
		SetSwitchValue(bIsSwitchActive);
	}
	else if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetName().Equals("bEmptyArray"))
	{
		bEmptyArray = false;
		AddSwitchableActor = nullptr;
		RemoveSwitchables();
	}
	else {
		Super::PostEditChangeProperty(PropertyChangedEvent);
	}
}
#endif // WITH_EDITOR

void USwitchComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	RemoveSwitchables();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

bool USwitchComponent::ToggleValue()
{
	SetSwitchValue(!bIsSwitchActive);
	return bIsSwitchActive;
}

void USwitchComponent::SetSwitchValue(bool bNewValue)
{
	bIsSwitchActive = bNewValue;
	if (SwitchableComponents.Num() > 0)
	{
		for (USwitchableComponent* SwitchableComp : SwitchableComponents)
		{
			if (SwitchableComp)
			{
				SwitchableComp->OnSwitchValueChanged(bIsSwitchActive);
			}
		}
	}
	OnValueChanged.Broadcast(bIsSwitchActive);
}

void USwitchComponent::RemoveSwitchable(USwitchableComponent* SwitchableToDelete)
{
	if (SwitchableToDelete)
	{
		SwitchableToDelete->RemoveSwitchComponent(this);
	}
	SwitchableComponents.Remove(SwitchableToDelete);
}


void USwitchComponent::RemoveSwitchables()
{
	for (USwitchableComponent* SwitchableToDelete : SwitchableComponents)
	{
		if (SwitchableToDelete)
		{
			SwitchableToDelete->RemoveSwitchComponent(this);
		}
	}
	SwitchableComponents.Empty();
}

void USwitchComponent::SetSwitchable(USwitchableComponent* NewSwitchable)
{
	if (NewSwitchable)
	{
		SwitchableComponents.AddUnique(NewSwitchable);
		NewSwitchable->AddSwitchComponent(this);
	}
}
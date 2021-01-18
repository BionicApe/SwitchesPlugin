// Created by Bionic Ape. All Rights Reserved.

#include "Components/SwitchableComponent.h"
#include "Components/SwitchComponent.h"

USwitchableComponent::USwitchableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USwitchableComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (SwitchComponents.Num() > 0)
	{
		TArray<USwitchComponent*> SwitchComponentsToRemove = TArray<USwitchComponent*>(SwitchComponents);
		for (USwitchComponent* SwitchToRemove : SwitchComponentsToRemove)
		{
			if (SwitchToRemove)
			{
				SwitchToRemove->RemoveSwitchable(this);//It calls USwitchableComponent::RemoveSwitchComponent internally
			}
		}
	}
	RefreshIsActivatedCache(true);

	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

bool USwitchableComponent::IsSwitchableActivated(bool bForceCalculate)
{
	if (bForceCalculate)
	{
		CalculateIsSwitchableActived();
	}
	return bIsActivatedCache;
}

void USwitchableComponent::AddSwitchComponent(USwitchComponent* NewSwitch)
{
	SwitchComponents.AddUnique(NewSwitch);
	RefreshIsActivatedCache(false);
}

void USwitchableComponent::RemoveSwitchComponent(USwitchComponent* SwitchToRemove)
{
	SwitchComponents.Remove(SwitchToRemove);
	RefreshIsActivatedCache(false);
}


void USwitchableComponent::RefreshIsActivatedCache(bool bForceBroadcast)
{
	bool bOldCache = bIsActivatedCache;
	CalculateIsSwitchableActived();
	const bool bIsValueDifferent = (bIsActivatedCache != bOldCache);

	if (bIsValueDifferent || bForceBroadcast)//we only broadcast if there's a change or if bForceBroadcast
	{
		OnResultChange.Broadcast(bIsActivatedCache);
	}
}

void USwitchableComponent::OnSwitchValueChanged(const bool NewValue)//we ignore NewValue since it's meaningless if we have more than 1 Switch
{
	RefreshIsActivatedCache(false);//there's no need to force broadcast
}

void USwitchableComponent::CalculateIsSwitchableActived()
{
	SwitchComponents.Remove(nullptr);//TODO: Check if there are components that are GC'd and still present in array

	bool bIsActivated = bNoSwitchsDefaultValue;

	if (SwitchComponents.Num() > 0)
	{
		switch (CalculationType)
		{
		case ESwitchableCalculationType::OR:
			bIsActivated = false;
			for (USwitchComponent* SwitchComponent : SwitchComponents)
			{
				bIsActivated = bIsActivated || SwitchComponent->IsSwitchActive();
			}
			break;
		case ESwitchableCalculationType::AND:
			bIsActivated = true;
			for (USwitchComponent* SwitchComponent : SwitchComponents)
			{
				bIsActivated = bIsActivated && SwitchComponent->IsSwitchActive();
			}
			break;
		}
	}

	bIsActivatedCache = bIsActivated;
}
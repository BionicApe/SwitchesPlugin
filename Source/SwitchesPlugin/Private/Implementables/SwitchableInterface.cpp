// Created by Bionic Ape. All Rights Reserved.

#include "Implementables/SwitchableInterface.h"


USwitchableInterface::USwitchableInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

USwitchableComponent* ISwitchableInterface::GetSwitchableComponent()
{
	return nullptr;
}
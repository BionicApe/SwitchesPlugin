// Created by Bionic Ape. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SwitchableInterface.generated.h"

class USwitchableComponent;

UINTERFACE(Blueprintable)
class SWITCHESPLUGIN_API USwitchableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class SWITCHESPLUGIN_API  ISwitchableInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual USwitchableComponent* GetSwitchableComponent();
};
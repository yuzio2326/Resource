// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IpNetDriver.h"
#include "CustomIpConnection.h"
#include "PersonalNetDriver.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API UPersonalNetDriver : public UIpNetDriver
{
	GENERATED_BODY()
	
public:
	/* Initializes the net connection class to use for new connections */
	virtual bool InitConnectionClass() override;
};

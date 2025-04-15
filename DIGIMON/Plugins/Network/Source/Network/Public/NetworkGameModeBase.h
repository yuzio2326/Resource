// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PersonalNetDriver.h"
#include "NetworkGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NETWORK_API ANetworkGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(Transient)
    UPersonalNetDriver* NetDriver = nullptr;
};

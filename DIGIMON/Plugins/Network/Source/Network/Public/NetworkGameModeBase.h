// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PersonalNetDriver.h"
#include "NetworkGameModeBase.generated.h"

/**
 * 
 */
UCLASS(config = Network)
class NETWORK_API ANetworkGameModeBase : public AGameModeBase, public FNetworkNotify
{
	GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(Transient)
    UPersonalNetDriver* NetDriver = nullptr;


    UPROPERTY(Config)
    FString Host;

    UPROPERTY(Config)
    int32 Port;
};

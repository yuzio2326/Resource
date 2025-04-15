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
	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;

protected:
    /**
     * 주어진 프로토콜을 사용하여 통신을 위해 설정된 소켓을 생성합니다. 이는 타입을 추론하는 대신 명시적으로 생성할 수 있게 합니다.
     *
     * @param ProtocolType   새로운 소켓을 할당할 프로토콜을 나타내는 FName입니다. 일반적으로 None 또는 FNetworkProtocolTypes의 값을 설정합니다.
     * @return               생성에 성공하면 FSocket을 반환하고, 실패하면 nullptr을 반환합니다.
     */
    virtual FUniqueSocket CreateSocketForProtocol(const FName& ProtocolType);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IpNetDriver.h"
#include "CustomIpConnection.h"
#include "PersonalNetDriver.generated.h"

/**
 * 
 */
UCLASS(config = Network)
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

    /**
     * 주어진 바인드 주소 정보를 사용하여 소켓을 생성, 초기화 및 바인드합니다.
     *
     * @param BindAddr              새 소켓을 바인드할 주소이며, 주소 프로토콜을 사용하여 CreateSocketForProtocol을 통해 소켓을 생성합니다.
     * @param Port                  주어진 바인드 주소와 함께 사용할 포트 번호입니다.
     * @param bReuseAddressAndPort  true로 설정하면, 주소가 사용 중이더라도 소켓을 바인드할 수 있게 설정합니다.
     * @param DesiredRecvSize       소켓의 수신 버퍼의 최대 크기입니다.
     * @param DesiredSendSize       소켓의 전송 버퍼의 최대 크기입니다.
     * @param Error                 오류가 발생할 경우 오류 메시지로 채워질 참조 문자열입니다.
     *
     * @return 소켓이 적절한 옵션으로 생성 및 바인드될 수 있으면 새 소켓에 대한 포인터를 반환하고, 그렇지 않으면 null을 반환합니다.
     */
    virtual FUniqueSocket CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error) override;
};

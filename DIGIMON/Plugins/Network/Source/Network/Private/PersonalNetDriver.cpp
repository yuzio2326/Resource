// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonalNetDriver.h"

bool UPersonalNetDriver::InitConnectionClass(void)
{
	//빌드후 찾기
	NetConnectionClassName = TEXT("/Script/Network.CustomIpConnection");
	return Super::InitConnectionClass();
}

bool UPersonalNetDriver::InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error)
{
	return Super::InitConnect(InNotify, ConnectURL, Error);
}

FUniqueSocket UPersonalNetDriver::CreateSocketForProtocol(const FName& ProtocolType)
{
    // TCP 소켓을 생성합니다.
    ISocketSubsystem* SocketSubsystem = GetSocketSubsystem();

    if (SocketSubsystem == NULL)
    {
        UE_LOG(LogNet, Warning, TEXT("UARNetDriver::CreateSocket: Unable to find socket subsystem"));
        return NULL;
    }

    return SocketSubsystem->CreateUniqueSocket(NAME_Stream, TEXT("CustomProtocal"), ProtocolType);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomIpConnection.h"
#include "Sockets.h"
#include "Net/Common/Packets/PacketTraits.h"

UCustomIpConnection::UCustomIpConnection()
{
	DisableAddressResolution();
}

void UCustomIpConnection::LowLevelSend(void* Data, int32 CountBits, FOutPacketTraits& Traits)
{
    //Size 가 잘못 되거나 Data가 nullptr면 Log띄우고
    if (CountBits == 0 || Data == nullptr)
    {
        UE_LOG(LogNet, Warning, TEXT("CountBits == 0 || Data == nullptr"));
        check(false);
        return;
    }

    int32 SentBytes = 0;
    //Socket안에서 Send 해서 보낼거임
    if (!Socket->Send((const uint8*)Data, CountBits, SentBytes))
    {
        UE_LOG(LogNet, Warning, TEXT("UARNetConnection: LowLevelSend: Server로 Data를 보낼 수 없습니다. %d"), CountBits);
        check(false);
    }

    //보낸거랑 요청한거랑 다르면 Log
    if (SentBytes != CountBits)
    {
        UE_LOG(LogNet, Warning, TEXT("UARNetConnection: LowLevelSend: SentBytes(%d) != CountBits(%d)"), SentBytes, CountBits);
        check(false);
        /*UARNetDriver* ARNetDriver = Cast<UARNetDriver>(Driver);
        ARNetDriver->Shutdown();*/
        return;
    }

    // 서버 Recv buffer가 가득 참(너무 빨리 Packet을 보냄)
    if (SentBytes == -1)
    {
        UE_LOG(LogNet, Warning, TEXT("UARNetConnection: LowLevelSend: SentBytes == -1"));
        check(false);
        /*UARNetDriver* ARNetDriver = Cast<UARNetDriver>(Driver);
        ARNetDriver->Shutdown();*/
        return;
    }
}

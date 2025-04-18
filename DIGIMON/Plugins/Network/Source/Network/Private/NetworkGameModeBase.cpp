// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameModeBase.h"
#include "EchoChannel.h"

void ANetworkGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	NetDriver = NewObject<UPersonalNetDriver>(this,TEXT("PersonalNetDriver"));
	FURL URL;
    URL.Host = Host;
    URL.Port = Port;
    FString OutError;
    if (!NetDriver->InitConnect(this, URL, OutError))
    {
        UE_LOG(LogTemp, Error, TEXT("Connect Failed"));
        RequestEngineExit(TEXT("Connect Failed"));
        return;
    }

    FString Message = TEXT("HelloUE!");
    UEchoChannel* EchoChannel = Cast<UEchoChannel>(NetDriver->ServerConnection->Channels[1]);
    FEchoMessage EchoMessage;
    std::wcsncpy(EchoMessage.Message, &Message[0], Message.Len());
    FNetEchoMessage<NMT_Echo>::Send(NetDriver->ServerConnection, EchoMessage);
}

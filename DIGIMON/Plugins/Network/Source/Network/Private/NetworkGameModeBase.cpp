// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameModeBase.h"

void ANetworkGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	NetDriver = NewObject<UPersonalNetDriver>(this,TEXT("PersonalNetDriver"));
	FURL URL;
    URL.Host = TEXT("127.0.0.1");
    URL.Port = 5555;
    FString OutError;
    if (!NetDriver->InitConnect(this, URL, OutError))
    {
        UE_LOG(LogTemp, Error, TEXT("Connect Failed"));
        RequestEngineExit(TEXT("Connect Failed"));
        return;
    }

}

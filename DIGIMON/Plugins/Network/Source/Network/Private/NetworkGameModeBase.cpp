// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameModeBase.h"

void ANetworkGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	NetDriver = NewObject<UPersonalNetDriver>(this,TEXT("PersonalNetDriver"));
	NetDriver->InitConnectionClass();
}

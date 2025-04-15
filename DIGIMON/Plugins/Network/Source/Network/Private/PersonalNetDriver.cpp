// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonalNetDriver.h"

bool UPersonalNetDriver::InitConnectionClass(void)
{
	//빌드후 찾기
	NetConnectionClassName = TEXT("/Script/Network.CustomIpConnection");
	return Super::InitConnectionClass();
}

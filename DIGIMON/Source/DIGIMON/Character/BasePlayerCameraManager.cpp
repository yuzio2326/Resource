// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayerCameraManager.h"

ABasePlayerCameraManager::ABasePlayerCameraManager()
{
	//pitch 제한	camera 상하 시야각 제한
	ViewPitchMin = -50.0;
	ViewPitchMax = 40.0;

}

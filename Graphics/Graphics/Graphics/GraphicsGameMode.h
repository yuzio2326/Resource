// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyViewExtension.h"
#include "GraphicsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GRAPHICS_API AGraphicsGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

private: 
	TSharedPtr<FMyViewExtension, ESPMode::ThreadSafe> MyViewExtension;
};

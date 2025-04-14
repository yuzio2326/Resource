// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "SpawnMonsterChildComponent.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API USpawnMonsterChildComponent : public UChildActorComponent
{
	GENERATED_BODY()
public:
	USpawnMonsterChildComponent();
	void SetData(FDataTableRowHandle InDataTableRowHandle);
	
};

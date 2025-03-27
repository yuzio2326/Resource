// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Misc/ActorPool.h"
#include "Effect/Effect.h"
//#include "Effect/EffectWithDecal.h"
#include "ActorPoolSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API UActorPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SpawnEffect(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);
	//void SpawnHitEffectWithDecal(const FTransform& SpawnTransform, const FDataTableRowHandle& InDataTableRowHandle);
	// ㄴ> decal 굳이? 그냥 spawn으로만 해도 ㄱㅊ을거 같은데?
	
protected:
	/** Called when world is ready to start gameplay before the game mode transitions to the correct state and call BeginPlay on all actors */
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	FCircularActorPool<AEffect> EffectPool;
	//FCircularActorPool<AEffectWithDecal> HitEffectDecalPool;
};

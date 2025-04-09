// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ProjectileAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API UProjectileAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UProjectileAnimNotify();

	FRotator GetPlayerProjectileRotation(const FVector& InProjectSpawnLocation, class UCameraComponent* InCameraComponent);
	FRotator GetPawnProjectileRotation(const FVector& InProjectSpawnLocation, class USkeletalMeshComponent* InSkeletalMeshComponent);
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomComponent/SkillComponent.h"
#include "CustomComponent/StatusComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/BasePlayer.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "PartyMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API APartyMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

protected:

	void CheckSpawnRadius();

	UFUNCTION()
	void OnDamaged(float CurrentHP, float MaxHP);
	UFUNCTION()
	void PlayerOnDamaged();

	UFUNCTION()
	void ResetOnDamaged();

	void FindPlayerByPerception();

	void MoveRandomPlace();

	UFUNCTION()
	void OnAttack(bool InIsAttacking);

	UFUNCTION()
	void OnUseSkill(bool InUsingSkill, bool InCanUseSkill, bool InIsRangeSkill);



public:
	void BaseAgro(bool IsBoss) { bBaseAgro = IsBoss; }

	void CheckStopAI();

	
protected:
	bool bDamaged = false;
	bool bUsingSkill = false;
	bool bBaseAgro = false;

	bool IsOwnPlayer = false;

	UPROPERTY()
	UStatusComponent* StatusComponentRef;
	UPROPERTY()
	UStatusComponent* OwnerPlayerStatusComponentRef;

	UPROPERTY()
	USkillComponent* SkillComponentRef;
	UPROPERTY()
	ABasePlayer* OwnerPlayer;


};

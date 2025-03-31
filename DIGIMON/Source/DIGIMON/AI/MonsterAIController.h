// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"


#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMON_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDamaged(float CurrentHP, float MaxHP);

	UFUNCTION()
	void ResetOnDamaged();

	void FindPlayerByPerception();
	virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);

	UFUNCTION()
	void OnAttack();

	UFUNCTION()
	void OnUseSkill(bool InUsingSkill, bool InCanUseSkill, bool InIsRangeSkill);



public:
	void CheckStopAI();


protected:
	bool bDamaged = false;
	bool bUsingSkill = false;
	bool bBossAgro = false;

	UPROPERTY()
	UStatusComponent* StatusComponentRef;

	UPROPERTY()
	USkillComponent* SkillComponentRef;


};

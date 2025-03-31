// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MonsterAIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	



}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	StatusComponentRef = InPawn->GetComponentByClass<UStatusComponent>();
	StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);

	SkillComponentRef = InPawn->GetComponentByClass<USkillComponent>();
	//SkillComponentRef->OnUsingSkill.AddDynamic(this, &ThisClass::OnUseSkill);
}

void AMonsterAIController::Tick(float DeltaTime)
{
}

void AMonsterAIController::OnDamaged(float CurrentHP, float MaxHP)
{
}

void AMonsterAIController::ResetOnDamaged()
{
}

void AMonsterAIController::FindPlayerByPerception()
{
}

void AMonsterAIController::SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority)
{
}

void AMonsterAIController::OnAttack()
{
}

void AMonsterAIController::OnUseSkill(bool InUsingSkill, bool InCanUseSkill, bool InIsRangeSkill)
{
}

void AMonsterAIController::CheckStopAI()
{
}

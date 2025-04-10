// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PartyMonsterAIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void APartyMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(BrainComponent))
	{
		UBehaviorTree* BehaviorTree = LoadObject<UBehaviorTree>(nullptr, TEXT("/Script/AIModule.BehaviorTree'/Game/Digimon/AI/BT_BasePartyMonster.BT_BasePartyMonster'"));
		check(BehaviorTree);
		RunBehaviorTree(BehaviorTree);
	}

	//Spawn 위치 기준 일정 범위 이상 못나가게 하려고 할때 쓸 예정
	APawn* OwningPawn = GetPawn();
	FVector FSpawnLocation = OwningPawn->GetActorLocation();
	Blackboard->SetValueAsVector(TEXT("SpwanPosition"), FSpawnLocation);

	IsOwnPlayer = SkillComponentRef->GetOwnerPlayer();;
}

void APartyMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	StatusComponentRef = InPawn->GetComponentByClass<UStatusComponent>();
	StatusComponentRef->OnHPChanged.AddDynamic(this, &ThisClass::OnDamaged);

	SkillComponentRef = InPawn->GetComponentByClass<USkillComponent>();
	SkillComponentRef->OnUsingSkill.AddDynamic(this, &ThisClass::OnUseSkill);
	SkillComponentRef = InPawn->GetComponentByClass<USkillComponent>();
	SkillComponentRef->FOnAttack.AddDynamic(this, &ThisClass::OnAttack);
}

void APartyMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckStopAI();

	//Test용 실전에서는 damage만을 이용해서 player를 타게팅해서 쫓아오게 할거임
	if (!bDamaged)
	{
		FindPlayerByPerception();
	}

	// Damaged일때는 안쓸지는 고민중
	//spawn 위치로부터 일정 거리 벗어나면 돌아가기 위한 용도
	CheckSpawnRadius();
}

void APartyMonsterAIController::CheckSpawnRadius()
{
	FVector FSpawnLocation = Blackboard->GetValueAsVector(TEXT("SpwanPosition"));
	APawn* OwningPawn = GetPawn();
	FVector OwningPawnLocation = OwningPawn->GetActorLocation();
	//이동 반경
	float Radius = 2000;

	float Distance = FVector::Dist(FSpawnLocation, OwningPawnLocation);
	if (Distance > Radius) { Blackboard->SetValueAsBool(TEXT("OutRangedSpawn"), true); }
	else { Blackboard->SetValueAsBool(TEXT("OutRangedSpawn"), false); }
}

void APartyMonsterAIController::OnDamaged(float CurrentHP, float MaxHP)
{
	bDamaged = true;
	AController* Instigator_ = StatusComponentRef->GetLastInstigator();
	APawn* InstigatorPawn = Instigator_->GetPawn();
	check(InstigatorPawn);
	Blackboard->SetValueAsObject(TEXT("DetectTarget"), Cast<UObject>(InstigatorPawn));
	Blackboard->SetValueAsBool(TEXT("OnDamage"), true);

	//5초뒤 어그로 리셋
	//UKismetSystemLibrary::K2_SetTimer(this, TEXT("ResetOnDamagedMontage"), 1.f, false);
}

void APartyMonsterAIController::ResetOnDamaged()
{
	bDamaged = false;
}

void APartyMonsterAIController::FindPlayerByPerception()
{
	APawn* OwningPawn = GetPawn();
	if (UAIPerceptionComponent* AIPerceptionComponent = OwningPawn->GetComponentByClass<UAIPerceptionComponent>())
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISenseConfig_Sight::StaticClass(), OutActors);

		bool bFound = false;
		for (AActor* It : OutActors)
		{
			if (ACharacter* DetectedPlayer = Cast<ACharacter>(It))
			{
				bFound = true;
				Blackboard->SetValueAsObject(TEXT("DetectPlayer"), Cast<UObject>(DetectedPlayer));
				break;
			}
		}
		//if (!bFound)
		//{
		//	Blackboard->ClearValue(TEXT("DetectPlayer"));
		//}
	}
}

void APartyMonsterAIController::MoveRandomPlace()
{
	FVector FSpawnLocation = Blackboard->GetValueAsVector(TEXT("SpwanPosition"));

	//random 반경 
	float Radius = 2000;
}

void APartyMonsterAIController::OnAttack(bool InIsAttacking)
{
	Blackboard->SetValueAsBool(TEXT("Attacking"), InIsAttacking);
}

void APartyMonsterAIController::OnUseSkill(bool InUsingSkill, bool InCanUseSkill, bool InIsRangeSkill)
{
	Blackboard->SetValueAsBool(TEXT("UsingSkill"), InUsingSkill);
	Blackboard->SetValueAsBool(TEXT("CanUseSkill"), InCanUseSkill);
	Blackboard->SetValueAsBool(TEXT("CanUseRangeSkill"), InIsRangeSkill);
}

void APartyMonsterAIController::CheckStopAI()
{
	APawn* OwningPawn = GetPawn();

	// Montage가 Play 중이라면 BT 내부에서 AI 진행을 멈춘다
	const bool bMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();

	const UAnimMontage* CurrentMontage = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->GetCurrentActiveMontage();
	const float CurrentPosition = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->Montage_GetPosition(CurrentMontage);
	const float MontageLength = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->Montage_GetPlayRate(CurrentMontage);
	bool StopAI = false;
	//A가 사용중이면 Stop, A가 사용중인데 0.2보다 낮으면 Play가 되어야함
	if (MontageLength > 0.2f && bMontagePlaying) { StopAI = true; }
	else { StopAI = false; }

	Blackboard->SetValueAsBool(TEXT("MontagePlaying"), StopAI);

	if (!StopAI)
	{
		Blackboard->SetValueAsBool(TEXT("UsingSkill"), false);
		Blackboard->SetValueAsBool(TEXT("OnDamage"), false);
	}
}

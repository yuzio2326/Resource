// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/PartyMonster.h"
#include "Kismet/KismetSystemLibrary.h"
//CanChange
#include "AI/MonsterAIController.h"

// Sets default values
APartyMonster::APartyMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	SkeletalMeshComponent->SetupAttachment(DefaultSceneRoot);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	//use actorpool and SetActorEnableCollision


	/*Add All Data */

	//ADDMovementComponent Later
	MovementComponent = CreateDefaultSubobject<UAdvanceFloatingPawnMovement>(TEXT("MovementComponent"));
	check(MovementComponent);
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	check(StatusComponent);
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("MonsterSkillComponent"));
	check(SkillComponent);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfig_Sight->SightRadius = 800.f;
	AISenseConfig_Sight->LoseSightRadius = 1000.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 120.f;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

}

void APartyMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	BaseDataTableRowHandle = InDataTableRowHandle;
	if (BaseDataTableRowHandle.IsNull()) { return; }
	//Player Team 이라서 Player 쪽으로 
	FBasePawnData* Data = BaseDataTableRowHandle.GetRow<FBasePawnData>(TEXT("Player"));
	if (!Data) { ensure(false); return; }
	PawnData = Data;

	//AI 나중에 추가하기
	AIControllerClass = PawnData->AIControllerClass;



	//Speed 조절
	MovementComponent->MaxSpeed = PawnData->MovementMaxSpeed;



	if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != PawnData->CollisionClass)
	{
		EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
		CollisionComponent = NewObject<UShapeComponent>(this, PawnData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
		CollisionComponent->RegisterComponent();
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Player);
		CollisionComponent->SetCanEverAffectNavigation(false);
		SetRootComponent(CollisionComponent);
		DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
		DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

		//Forcheck visable true
		CollisionComponent->SetVisibility(true);
	}

	if (USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent))
	{
		SphereComponent->SetSphereRadius(PawnData->CollisionSphereRadius);
	}
	else if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent))
	{
		BoxComponent->SetBoxExtent(PawnData->CollisionBoxExtent);
	}
	else if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent))
	{
		CapsuleComponent->SetCapsuleSize(PawnData->CollisionCapsuleRadius, PawnData->CollisionCapsuleHalfHeight);
	}

	SkeletalMeshComponent->SetSkeletalMesh(PawnData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(PawnData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(PawnData->MeshTransform);

	if (PawnData->Level != 0 && PawnData->HP != 0 && PawnData->PawnType != 0)
	{
		StatusComponent->StatusSetting(PawnData->Level, PawnData->EXP, PawnData->HP, PawnData->MP, PawnData->STR, PawnData->STR_DEF, PawnData->INT, PawnData->INT_DEF, PawnData->PawnType);
	}

	AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	if (!IsValid(CollisionComponent))
	{
		int b = 0;
	}
	if (CollisionComponent->GetClass() != PawnData->CollisionClass)
	{
		int a = 0;
	}
}

void APartyMonster::SetSkillData(const FDataTableRowHandle& InSkillDataTableRowHandle)
{
	PawnData->OwnSkillData = InSkillDataTableRowHandle;
	if (PawnData->OwnSkillData.IsNull()) { return; }

	/*고민중*/
	FSkillTableRow* Data = PawnData->OwnSkillData.GetRow<FSkillTableRow>(TEXT("MonsterSkillData"));
	if (!Data) { ensure(false); return; }
	MonsterSkillData = Data;

	//여기에 skill data setting중이라..
	SkillComponent->SetData(InSkillDataTableRowHandle);


	int32 CheckSkillNum = MonsterSkillData->SkillDataArray.Num();

}

void APartyMonster::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData(BaseDataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void APartyMonster::PostLoad()
{
	Super::PostLoad();
}

void APartyMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void APartyMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Party M<onster 임으로 다 필요 없음
	//AIController 만들고 patrol 하고난 이후 주석 풀기		AMonsterAIController 대신 다른걸로 바뀔수 있음
	//if (AMonsterAIController* EnemyAIController = Cast<AMonsterAIController>(Controller))
	//{
		//EnemyAIController->SetPatrolPath(PatrolPathRef->GetPath());
		//if (PawnData)
		//{
		//	EnemyAIController->BaseAgro(PawnData->BossVision);
		//}
	//}
}

// Called when the game starts or when spawned
void APartyMonster::BeginPlay()
{
	Super::BeginPlay();
	SetData(BaseDataTableRowHandle);
	SetSkillData(PawnData->OwnSkillData);
}

void APartyMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(BaseDataTableRowHandle);
	SetActorTransform(Transform);
}

// Called every frame
void APartyMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float checkEXP = StatusComponent->GetEXP();

}

void APartyMonster::SetOwnerPlayer(ABasePlayer* InOwnPlayerTarget)
{
	if (InOwnPlayerTarget)
	{
		IsOwnPlayer.Broadcast(true, InOwnPlayerTarget);
	}
	else 
	{
		IsOwnPlayer.Broadcast(false, nullptr);
	}
}

void APartyMonster::OnDie()
{
	AnimInstance->Montage_Pause(CurrentDieMontage);
}

float APartyMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }

	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}

	if (StatusComponent->IsDie() && !PawnData->DieMontage.IsEmpty())
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		const int64 Index = FMath::RandRange(0, PawnData->DieMontage.Num() - 1);
		CurrentDieMontage = PawnData->DieMontage[Index];

		AnimInstance->Montage_Play(CurrentDieMontage);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			PawnData->DieMontage[Index]->GetPlayLength() - 0.5f, false);
	}
	else if (!StatusComponent->IsDie() && !PawnData->HitReactMontage.IsEmpty())
	{
		const int64 HitReactIndex = FMath::RandRange(0, PawnData->HitReactMontage.Num() - 1);
		AnimInstance->Montage_Play(PawnData->HitReactMontage[HitReactIndex]);
	}

	return 0.0f;
}



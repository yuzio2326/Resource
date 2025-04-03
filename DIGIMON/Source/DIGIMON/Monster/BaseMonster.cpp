// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h"
#include "AI/MonsterAIController.h"
#include "BaseMonster.h"

// Sets default values
ABaseMonster::ABaseMonster()
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
	AISenseConfig_Sight->SightRadius = 500.f;
	AISenseConfig_Sight->LoseSightRadius = 700.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 120.f;
	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

}

void ABaseMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	MonsterDataTableRowHandle = InDataTableRowHandle;
	if (MonsterDataTableRowHandle.IsNull()) { return; }
	FBaseMonsterTableRow* Data = MonsterDataTableRowHandle.GetRow<FBaseMonsterTableRow>(TEXT("Enemy"));
	if (!Data) { ensure(false); return; }
	MonsterData = Data;

	//AI 나중에 추가하기
	AIControllerClass = MonsterData->AIControllerClass;


	//Speed 조절
	MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

	if (!IsValid(CollisionComponent))
	{
		int b = 0;
	}
	if (CollisionComponent->GetClass() != MonsterData->CollisionClass)
	{
		int a = 0;
	}

	if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != MonsterData->CollisionClass)
	{
		EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
		CollisionComponent = NewObject<UShapeComponent>(this, MonsterData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
		CollisionComponent->RegisterComponent();
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::Enemy);
		CollisionComponent->SetCanEverAffectNavigation(false);
		SetRootComponent(CollisionComponent);
		DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
		DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
		
		//Forcheck visable true
		CollisionComponent->SetVisibility(true);
	}

	if (USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent))
	{
		SphereComponent->SetSphereRadius(MonsterData->CollisionSphereRadius);
	}
	else if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent))
	{
		BoxComponent->SetBoxExtent(MonsterData->CollisionBoxExtent);
	}
	else if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent))
	{
		CapsuleComponent->SetCapsuleSize(MonsterData->CollisionCapsuleRadius, MonsterData->CollisionCapsuleHalfHeight);
	}

	SkeletalMeshComponent->SetSkeletalMesh(MonsterData->SkeletalMesh);
	SkeletalMeshComponent->SetAnimClass(MonsterData->AnimClass);
	SkeletalMeshComponent->SetRelativeTransform(MonsterData->MeshTransform);

	if (MonsterData->Level != 0 && MonsterData->HP != 0 && MonsterData->PawnType != 0)
	{
		StatusComponent->StatusSetting(MonsterData->Level, MonsterData->EXP, MonsterData->HP, MonsterData->MP, MonsterData->STR, MonsterData->STR_DEF, MonsterData->INT, MonsterData->INT_DEF, MonsterData->PawnType);
	}

	AnimInstance = SkeletalMeshComponent->GetAnimInstance();

}

void ABaseMonster::SetSkillData(const FDataTableRowHandle& InSkillDataTableRowHandle)
{
	MonsterData->OwnSkillData = InSkillDataTableRowHandle;
	if (MonsterData->OwnSkillData.IsNull()) { return; }

	/*고민중*/
	FSkillTableRow* Data = MonsterData->OwnSkillData.GetRow<FSkillTableRow>(TEXT("MonsterSkillData"));
	if (!Data) { ensure(false); return; }
	MonsterSkillData = Data;

	//여기에 skill data setting중이라..
	SkillComponent->SetData(InSkillDataTableRowHandle);


	int32 CheckSkillNum = MonsterSkillData->SkillDataArray.Num();

}

void ABaseMonster::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData(MonsterDataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void ABaseMonster::PostLoad()
{
	Super::PostLoad();
}

void ABaseMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
	Super::PostLoadSubobjects(OuterInstanceGraph);
}

void ABaseMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	//AIController 만들고 patrol 하고난 이후 주석 풀기
	if (AMonsterAIController* EnemyAIController = Cast<AMonsterAIController>(Controller))
	{
		//EnemyAIController->SetPatrolPath(PatrolPathRef->GetPath());
		if (MonsterData)
		{
			EnemyAIController->BaseAgro(MonsterData->BossVision);
		}
	}
	
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	SetData(MonsterDataTableRowHandle);
	SetSkillData(MonsterData->OwnSkillData);
}

void ABaseMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(MonsterDataTableRowHandle);
	SetActorTransform(Transform);
}

float ABaseMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.f; }

	float DamageResult = StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (FMath::IsNearlyZero(DamageResult)) { return 0.0; }

	if (Controller)
	{
		Controller->StopMovement();
	}

	if (StatusComponent->IsDie() && !MonsterData->DieMontage.IsEmpty())
	{
		if (Controller)
		{
			Controller->Destroy();
		}
		SetActorEnableCollision(false);

		const int64 Index = FMath::RandRange(0, MonsterData->DieMontage.Num() - 1);
		CurrentDieMontage = MonsterData->DieMontage[Index];

		AnimInstance->Montage_Play(CurrentDieMontage);
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnDie"),
			MonsterData->DieMontage[Index]->GetPlayLength() - 0.5f, false);
	}
	else if (!StatusComponent->IsDie() && !MonsterData->HitReactMontage.IsEmpty())
	{
		const int64 HitReactIndex = FMath::RandRange(0, MonsterData->HitReactMontage.Num() - 1);
		AnimInstance->Montage_Play(MonsterData->HitReactMontage[HitReactIndex]);
	}

	return 0.0f;
}

void ABaseMonster::OnDie()
{
	AnimInstance->Montage_Pause(CurrentDieMontage);


	//PaperBurn Parts
	//const int32 MaterialNum = SkeletalMeshComponent->GetSkinnedAsset()->GetMaterials().Num();
	//MaterialInstanceDynamics.Reserve(MaterialNum);
	//for (int32 i = 0; i < MaterialNum; ++i)
	//{
	//	MaterialInstanceDynamics.Add(SkeletalMeshComponent->CreateDynamicMaterialInstance(i));
	//}

	//PaperBurnEffectTimelineComponent->Play();
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



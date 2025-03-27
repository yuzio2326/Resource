// Fill out your copyright notice in the Description page of Project Settings.


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
	//MovementComponent = CreateDefaultSubobject<UAdvanceFloatingPawnMovement>(TEXT("MovementComponent"));
	//check(MovementComponent);

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	check(StatusComponent);
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("MonsterSkillComponent"));
	check(SkillComponent);



}

void ABaseMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	BaseMonsterDataTableRowHandle = InDataTableRowHandle;
	if (BaseMonsterDataTableRowHandle.IsNull()) { return; }
	FBaseMonsterTableRow* Data = BaseMonsterDataTableRowHandle.GetRow<FBaseMonsterTableRow>(TEXT("Enemy"));
	if (!Data) { ensure(false); return; }
	MonsterData = Data;

	//AI 나중에 추가하기
	//AIControllerClass = MonsterData->AIControllerClass;



	//MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

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

	//AnimInstance = SkeletalMeshComponent->GetAnimInstance();

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


	int32 CheckSkillNum = MonsterSkillData->SkillArray.Num();

}

void ABaseMonster::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData(BaseMonsterDataTableRowHandle);
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
	// 
	//if (PatrolPathRef)
	//{
	//	if (AMonsterAIController* EnemyAIController = Cast<AMonsterAIController>(Controller))
	//	{
	//		EnemyAIController->SetPatrolPath(PatrolPathRef->GetPath());
	//		if (MonsterData)
	//		{
	//			EnemyAIController->BossAgro(MonsterData->BossVision);

	//		}
	//	}
	//}
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	SetData(BaseMonsterDataTableRowHandle);
	SetSkillData(MonsterData->OwnSkillData);
}

void ABaseMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(BaseMonsterDataTableRowHandle);
	SetActorTransform(Transform);
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


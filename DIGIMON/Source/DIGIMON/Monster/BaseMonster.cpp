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




}

void ABaseMonster::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	BasePawnDataTableRowHandle = InDataTableRowHandle;
	if (BasePawnDataTableRowHandle.IsNull()) { return; }
	FBaseMonsterTableRow* Data = BasePawnDataTableRowHandle.GetRow<FBaseMonsterTableRow>(TEXT("Enemy"));
	if (!Data) { ensure(false); return; }
	MonsterData = Data;

	//AI 나중에 추가하기
	//AIControllerClass = MonsterData->AIControllerClass;



	//MovementComponent->MaxSpeed = MonsterData->MovementMaxSpeed;

	//if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != MonsterData->CollisionClass)
	//{
	//	EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
	//	CollisionComponent = NewObject<UShapeComponent>(this, MonsterData->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
	//	CollisionComponent->RegisterComponent();
	//	CollisionComponent->SetCollisionProfileName(CollisionProfileName::Enemy);
	//	CollisionComponent->SetCanEverAffectNavigation(false);
	//	SetRootComponent(CollisionComponent);
	//	DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
	//	DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//}

	//if (USphereComponent* SphereComponent = Cast<USphereComponent>(CollisionComponent))
	//{
	//	SphereComponent->SetSphereRadius(MonsterData->CollisionSphereRadius);
	//}
	//else if (UBoxComponent* BoxComponent = Cast<UBoxComponent>(CollisionComponent))
	//{
	//	BoxComponent->SetBoxExtent(MonsterData->CollisionBoxExtent);
	//}
	//else if (UCapsuleComponent* CapsuleComponent = Cast<UCapsuleComponent>(CollisionComponent))
	//{
	//	CapsuleComponent->SetCapsuleSize(MonsterData->CollisionCapsuleRadius, MonsterData->CollisionCapsuleHalfHeight);
	//}

	//SkeletalMeshComponent->SetSkeletalMesh(MonsterData->SkeletalMesh);
	//SkeletalMeshComponent->SetAnimClass(MonsterData->AnimClass);
	//SkeletalMeshComponent->SetRelativeTransform(MonsterData->MeshTransform);

	//if (MonsterData->HP != 0 && MonsterData->DMG != 0)
	//{
	//	StatusComponent->StatusSetting(MonsterData->HP, MonsterData->DMG);
	//	MonsterDMG = MonsterData->DMG;
	//	MonsterHP = MonsterData->HP;
	//}

	//AnimInstance = SkeletalMeshComponent->GetAnimInstance();

}

void ABaseMonster::SetSkillData(const FDataTableRowHandle& InSkillDataTableRowHandle)
{

}

void ABaseMonster::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);
	if (DuplicateMode == EDuplicateMode::Normal)
	{
		FTransform Backup = GetActorTransform();
		CollisionComponent->DestroyComponent();
		SetData(BasePawnDataTableRowHandle);
		SetActorTransform(Backup);
	}
}

void ABaseMonster::PostLoad()
{
}

void ABaseMonster::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
{
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
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


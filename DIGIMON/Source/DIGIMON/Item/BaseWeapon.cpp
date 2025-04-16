// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABaseWeapon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FWeaponTableRow* Data = DataTableRowHandle.GetRow<FWeaponTableRow>(TEXT("Weapon"));
	if (!Data) { ensure(false); return; }
	WeaponTableRow = Data;

	SkeletalMeshComponent->SetSkeletalMesh(Data->SkeletalMesh);
	SkeletalMeshComponent->SetRelativeTransform(Data->Transform);
	
	USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	check(MeshComponent);
	{
		OwningPawn = Cast<APawn>(GetOwner());
		check(OwningPawn);
		OwningPawnBodyMesh = OwningPawn->GetComponentByClass<USkeletalMeshComponent>();
		check(OwningPawnBodyMesh);
		BasicAnimInstance = Cast<UBaisicCharacterAnimInstance>(MeshComponent->GetAnimInstance());
		check(BasicAnimInstance);

		OwnerStatusComponent = OwningPawn->GetComponentByClass<UStatusComponent>();
		check(OwnerStatusComponent);
		{
			BasicAnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
		}
	}
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FWeaponTableRow::FWeaponTableRow()
{
}

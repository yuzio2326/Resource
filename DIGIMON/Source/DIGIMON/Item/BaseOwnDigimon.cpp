// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseOwnDigimon.h"

// Sets default values
ABaseOwnDigimon::ABaseOwnDigimon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseOwnDigimon::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{

}

// Called when the game starts or when spawned
void ABaseOwnDigimon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseOwnDigimon::SpawnOwnMonster()
{

	//Muzzle 관련을 player Spawn Position으로 바꾸고 data도 바꾸도록 하자

	USkeletalMeshComponent* OwnerSkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();

	OwningPawn = Cast<APawn>(GetOwner());

	ABasePlayer* BasePlayer = Cast<ABasePlayer>(OwningPawn);
	check(BasePlayer);
	UInventoryComponent* OwnerInventory = BasePlayer->GetInventoryComponent();
	check(OwnerInventory);
	
	FOwnDigimonTableRow* BaseOwn = BasePawnDataTable.GetRow<FOwnDigimonTableRow>(TEXT("OwningMonster"));

	//ProjectileTableRow = CurrentSkilldata.ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("SkillProjectile"));
	//check(ProjectileTableRow);



	UWorld* World = OwningPawn->GetWorld();
	APartyMonster* PartyMonster = World->SpawnActorDeferred<APartyMonster>(BaseOwn->PartyMonsterClass,
		FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	PartyMonster->SetData(BasePawnDataTable);

	const FVector SpawnPartyLocation = OwnerSkeletalMeshComponent->GetSocketLocation(SocketName::SpawnParty);
	const FRotator SpawnPartyRotation = OwnerSkeletalMeshComponent->GetSocketRotation(SocketName::SpawnParty);
	

	FTransform NewTransform;
	NewTransform.SetLocation(SpawnPartyLocation);
	PartyMonster->FinishSpawning(NewTransform);

}

// Called every frame
void ABaseOwnDigimon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FOwnDigimonTableRow::FOwnDigimonTableRow()
	: PartyMonsterClass(APartyMonster::StaticClass())
{
}

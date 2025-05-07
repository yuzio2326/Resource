// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"
#include "Misc/Utils.h"
#include "Kismet/GameplayStatics.h"
#include "Data/PawnData.h"
#include "CustomComponent/StatusComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	//Collider = CreateDefaultSubobject<UShapeComponent>(TEXT("Collider"));
	//Collider->SetCollisionProfileName(CollisionProfileName::PawnTrigger);
	//RootComponent = Collider;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	//PrimaryActorTick.bCanEverTick = true;
	//OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
}

void ABaseItem::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FItemTableRow* Data = DataTableRowHandle.GetRow<FItemTableRow>(TEXT("ItemPack"));
	if (!Data) { ensure(false); return; }

	//�ϴ� static mesh�� 
	StaticMeshComponent->SetStaticMesh(Data->StaticMesh);
	StaticMeshComponent->SetRelativeScale3D(Data->Scale);

	if (!IsValid(CollisionComponent) || CollisionComponent->GetClass() != Data->CollisionClass)
	{
		EObjectFlags SubobjectFlags = GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject;
		CollisionComponent = NewObject<UShapeComponent>(this, Data->CollisionClass, TEXT("CollisionComponent"), SubobjectFlags);
		CollisionComponent->RegisterComponent();
		CollisionComponent->SetCollisionProfileName(CollisionProfileName::PawnTrigger);
		CollisionComponent->SetCanEverAffectNavigation(false);
		SetRootComponent(CollisionComponent);
		DefaultSceneRoot->SetRelativeTransform(FTransform::Identity);
		DefaultSceneRoot->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

		//Forcheck visable true
		CollisionComponent->SetVisibility(true);
	}


	//Overlap �� ���� ���� �ϱ�
	if (USphereComponent* SphereComponent = Cast<USphereComponent>(Collider))
	{
		const float ScaledRadius = FMath::Max3(Data->Scale.X, Data->Scale.Y, Data->Scale.Z);

		if (Data->StaticMesh)
		{
			FBoxSphereBounds BoxSphereBounds = Data->StaticMesh->GetBounds();
			SphereComponent->SetSphereRadius(ScaledRadius * BoxSphereBounds.SphereRadius);
		}
	}
}

void ABaseItem::UseItem(APawn* Pawn)
{
	if (DataTableRowHandle.IsNull()) { return; }
	FItemTableRow* Data = DataTableRowHandle.GetRow<FItemTableRow>(TEXT("Item"));
	if (!Data) { ensure(false); return; }

	// ������� �Ҹ�ǰ�̸� player �� ���� ���� status ���� ui�� �߰��� �߰� �ű⿡�� ���ϴ� ��� ���� ��� �ش� ����� ����ϵ��� �Ѵ�
	// Temp_UseItemTarget UI ����� �������� �����ؼ� �����
	
	//������̸� �׳� �ش��ϴ� ������ ��� ���� ����� ���� 
	//chat ����� ���� status ����ϴ� ��ġ�� chat �ֱ�

	//���߿� Target(Player, or PartyMonster) ���ؼ� ����Ҽ� �ֵ��� �ϱ�
	UStatusComponent* PlayerStatus = Pawn->GetComponentByClass<UStatusComponent>();

	FPawnTableRow* PawnData = DataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Character"));
	if (!Data->Sound.IsNull())
	{
		const FVector Location = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Data->Sound, Location, Data->VolumeMultiplier);
	}

}

void ABaseItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetData(DataTableRowHandle);
}

void ABaseItem::SetWeaponMesh(UStaticMesh* NewMesh)
{
	//if (NewMesh && WeaponMesh)
	//{
	//	WeaponMesh->SetStaticMesh(NewMesh);
	//}
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FItemTableRow::FItemTableRow()
	: ItemClass(ABaseItem::StaticClass())
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Skills/Projectile.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/ActorPoolSubsystem.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetupAttachment(DefaultSceneRoot);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	if (ProjectileData)
	{
		ProjectileMovementComponent->InitialSpeed = ProjectileData->InitialSpeed;
		ProjectileMovementComponent->MaxSpeed = ProjectileData->MaxSpeed;
		ProjectileMovementComponent->ProjectileGravityScale = ProjectileData->ProjectileGravityScale;
		InitialLifeSpan = ProjectileData->InitialSpeed;
	}
	else
	{
		ProjectileMovementComponent->InitialSpeed = 350.0;
		ProjectileMovementComponent->MaxSpeed = 10000.0;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0;
		InitialLifeSpan = 5.f;

	}

	ProjectileMovementComponent->UpdatedComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(CollisionProfileName::Projectile);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	

}

void AProjectile::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FProjectileTableRow* Data = DataTableRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
	if (!Data) { ensure(false); return; }

	ProjectileData = Data;

	StaticMeshComponent->MoveIgnoreActors.Empty();
	StaticMeshComponent->MoveIgnoreActors.Add(GetOwner());

	StaticMeshComponent->SetStaticMesh(Data->StaticMesh);
	StaticMeshComponent->SetRelativeTransform(Data->Transform);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//data setting 이후 시점이라서 여기에 data가 있을 경우 기존 값을 바꾸도록 한다

}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetOwner()->GetActorLocation();
	if (!IsValid(this)) { return; }

	// BeginPlay 시점에 Overlapped 되면 들어 옴
	if (!bFromSweep)
	{
		Destroy();
		//check(false);
		return;
	}

	FTransform NewTransform;
	NewTransform.SetLocation(SweepResult.ImpactPoint);
	FRotator Rotation = UKismetMathLibrary::Conv_VectorToRotator(SweepResult.ImpactNormal);
	NewTransform.SetRotation(Rotation.Quaternion());
	GetWorld()->GetSubsystem<UActorPoolSubsystem>()->SpawnEffect(NewTransform, ProjectileData->HitEffectTableRowHandle);
	Destroy();

	UGameplayStatics::ApplyDamage(OtherActor, 1.f, GetInstigator()->GetController(), this, nullptr);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ChargeProjectile()
{
	FVector ForwardVec =  GetActorForwardVector();
	ProjectileMovementComponent->Velocity = ForwardVec * ProjectileData->bChargeTime * 1000;

}

FProjectileTableRow::FProjectileTableRow()
	: ProjectileClass(AProjectile::StaticClass())
{
}

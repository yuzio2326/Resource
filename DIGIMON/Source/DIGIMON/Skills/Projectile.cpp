#include "Skills/Projectile.h"
#include "Misc/Utils.h"
#include "Subsystem/ActorPoolSubsystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 10000.0;
	ProjectileMovementComponent->MaxSpeed = 10000.0;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0;
	InitialLifeSpan = 5.f;

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

	if (ProjectileData != nullptr)
	{
		
		if (ProjectileData->bProjetileCharge)
		{
			int32 ChrageTime = ProjectileData->bChargeTime;
			UKismetSystemLibrary::K2_SetTimer(this, TEXT("ChargeProjectile"), ChrageTime, false);
		}
		else 
		{
			ProjectileMovementComponent->InitialSpeed = 10000.0;
		}
		ProjectileMovementComponent->MaxSpeed = 10000.0;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0;
		InitialLifeSpan = 5.f;

	}
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector Location = GetActorLocation();
	if (!IsValid(this)) { return; }

	// BeginPlay 시점에 Overlapped 되면 들어 옴
	if (!bFromSweep)
	{
		Destroy();
		check(false);
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

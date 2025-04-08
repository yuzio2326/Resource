#include "Animation/ProjectileAnimNotify.h"
#include "Skills/Projectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/Utils.h"
#include "Character/BasePlayer.h"
#include "Monster/BaseMonster.h"


UProjectileAnimNotify::UProjectileAnimNotify()
{
	NotifyColor = FColor(255, 255, 255, 255);
}

FRotator UProjectileAnimNotify::GetPlayerProjectileRotation(const FVector& InProjectSpawnLocation, UCameraComponent* InCameraComponent)
{
	const FVector CameraForwardVector = InCameraComponent->GetForwardVector();
	const FVector DestinationLocation = InCameraComponent->GetComponentLocation() + CameraForwardVector * 5000.0;

	TArray<AActor*> IgnoreActors; IgnoreActors.Add(InCameraComponent->GetOwner());
	FHitResult HitResult;

	const ETraceTypeQuery TraceTypeQuery = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel4);
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(InCameraComponent->GetWorld(),
		InCameraComponent->GetComponentLocation(), DestinationLocation, TraceTypeQuery,
		false, IgnoreActors, EDrawDebugTrace::None, HitResult, true);

	FRotator Rotator;
	if (bHit)
	{
		Rotator = UKismetMathLibrary::FindLookAtRotation(InProjectSpawnLocation, HitResult.ImpactPoint);
	}
	else
	{
		Rotator = UKismetMathLibrary::FindLookAtRotation(InProjectSpawnLocation, DestinationLocation);
	}
	return Rotator;
}

void UProjectileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
#if WITH_EDITOR
	if (GIsEditor && MeshComp->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	//Owner 가지고 와서 
	APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
	check(OwningPawn);

	USkeletalMeshComponent* OwnerSkeletalMeshComponent = OwningPawn->GetComponentByClass<USkeletalMeshComponent>();
	check(OwnerSkeletalMeshComponent);

	const FVector MuzzleLocation = OwnerSkeletalMeshComponent->GetSocketLocation(SocketName::Muzzle);
	
#if WITH_EDITOR
	USkeletalMeshSocket const* SkeletalMeshSocket = OwnerSkeletalMeshComponent->GetSocketByName(SocketName::Muzzle);
	check(SkeletalMeshSocket);
#endif

	FRotator ProjectileRotator = FRotator::ZeroRotator;
	bool bIsPlayer = false;
	//Camera 보유시 Player 아닐시 AI
	if (UCameraComponent* CameraComponent = OwningPawn->GetComponentByClass<UCameraComponent>())
	{
		bIsPlayer = true;
		ProjectileRotator = GetPlayerProjectileRotation(MuzzleLocation, CameraComponent);
	}
	else
	{
		//Socket 의 tranform 배치함
		bIsPlayer = false;

	}
	
	//Player일 경우
	if (bIsPlayer)
	{
		ABasePlayer* PlayerCharacter = Cast<ABasePlayer>(OwningPawn);
		check(PlayerCharacter);
		//기본 스킬에 평타 넣으면 되려나?
		// 
		//const FBasePawnData* PawnData= PlayerCharacter->getbasepaw
	}
	else 
	{
		ABaseMonster* MonsterPawn = Cast<ABaseMonster>(OwningPawn);
		check(MonsterPawn);
		const FSkillTableRow* SkillTableRow = MonsterPawn->GetMonsterSkillDataTableRow();

		//skill data table 가지고 왔고 이제 여기서 프로젝타일 있는 곳까지 뽑아 와야돼..




		//const FBasePawnData
	}


	//AGun* GunActor = Cast<AGun>(WeaponActor);
	//check(GunActor);
	//const FGunTableRow* GunTableRow = GunActor->GetGunTableRow();
	//const FProjectileTableRow* ProjectileTableRow = GunTableRow->ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
	//check(ProjectileTableRow);

	UWorld* World = OwningPawn->GetWorld();
	//AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileTableRow->ProjectileClass,
		//FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//Projectile->SetData(GunTableRow->ProjectileRowHandle);

	//FTransform NewTransform;
	//NewTransform.SetLocation(MuzzleLocation);
	//NewTransform.SetRotation(ProjectileRotator.Quaternion());
	//Projectile->FinishSpawning(NewTransform);
}

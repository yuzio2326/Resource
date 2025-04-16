// Fill out your copyright notice in the Description page of Project Settings.

#include "Skills/Projectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/Utils.h"
#include "Character/BasePlayer.h"
#include "Monster/BaseMonster.h"
#include "Monster/PartyMonster.h"

#include "Animation/ProjectileAnimNotify.h"

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

FRotator UProjectileAnimNotify::GetPawnProjectileRotation(const FVector& InProjectSpawnLocation, USkeletalMeshComponent* InSkeletalMeshComponent)
{
	const FVector CameraForwardVector = InSkeletalMeshComponent->GetForwardVector();
	const FVector DestinationLocation = InSkeletalMeshComponent->GetComponentLocation() + CameraForwardVector * 5000.0;

	TArray<AActor*> IgnoreActors; IgnoreActors.Add(InSkeletalMeshComponent->GetOwner());
	FHitResult HitResult;

	const ETraceTypeQuery TraceTypeQuery = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel4);
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(InSkeletalMeshComponent->GetWorld(),
		InSkeletalMeshComponent->GetComponentLocation(), DestinationLocation, TraceTypeQuery,
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
	const FRotator MuzzleRotation = OwnerSkeletalMeshComponent->GetSocketRotation(SocketName::Muzzle);
#if WITH_EDITOR
	USkeletalMeshSocket const* SkeletalMeshSocket = OwnerSkeletalMeshComponent->GetSocketByName(SocketName::Muzzle);
	check(SkeletalMeshSocket);
#endif

	FRotator ProjectileRotator = FRotator::ZeroRotator;
	bool bIsPlayer = false;
	bool bIsPartyMonster = false;
	//Camera 보유시 Player 아닐시 AI 로 spawn Location Rotation 조절
	if (UCameraComponent* CameraComponent = OwningPawn->GetComponentByClass<UCameraComponent>())
	{
		bIsPlayer = true;
		ProjectileRotator = GetPlayerProjectileRotation(MuzzleLocation, CameraComponent);
	}
	else
	{
		//Socket 의 tranform 배치함
		bIsPlayer = false;
		FVector ForwardDirection = MuzzleRotation.Vector();
		FRotator ForwardRotation = ForwardDirection.Rotation();
		ProjectileRotator = ForwardRotation;
		AMonsterAIController* OwnMonsterAI = Cast<AMonsterAIController>(OwningPawn->GetController());

		//MonsterAI 로 캐스팅해서 Monster로 없으면 PartyMonster로
		if (OwnMonsterAI)
		{ 
			bIsPartyMonster = false; 
		}
		else
		{
			bIsPartyMonster = true; 			
		}
		
		//APartyMonster* PlayerCharacter = Cast<APartyMonster>(OwningPawn);
		//USkillComponent* PartyMonsterPawn = Cast<USkillComponent>(OwningPawn);
		//bIsPartyMonster = PlayerCharacter->OwningPlayer();
	}
	
	//Player일 경우
	if (bIsPlayer)
	{
		//USkillComponent* PlayerSkillComponent;
		FSkillDataRow CurrentSkilldata;
		//FProjectileTableRow* ProjectileTableRow;
		ABasePlayer* PlayerCharacter = Cast<ABasePlayer>(OwningPawn);
		check(PlayerCharacter);
		float Damage = PlayerCharacter->GetStatusComponent()->GetSTR();
		//ProjectileTableRow =
		//기본 스킬에 평타 넣으면 되려나?
		// 
		//const FBasePawnData* PawnData= PlayerCharacter->getbasepaw
		/*const FProjectileTableRow* ProjectileTableRow = GunTableRow->ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("Projectile"));
		check(ProjectileTableRow);*/
		//구현 필요함
	}
	else 
	{
		USkillComponent* MonsterSkillComponent;
		FSkillDataRow CurrentSkilldata;
		FProjectileTableRow* ProjectileTableRow;
		//Party Monster
		if (bIsPartyMonster)
		{
			APartyMonster* PartyMonsterPawn = Cast<APartyMonster>(OwningPawn);
			check(PartyMonsterPawn);
			MonsterSkillComponent = PartyMonsterPawn->GetMonsterSkilRow();
			check(MonsterSkillComponent);
			CurrentSkilldata = MonsterSkillComponent->GetCurrentSkillData();
			ProjectileTableRow = CurrentSkilldata.ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("SkillProjectile"));
			check(ProjectileTableRow);

			UStatusComponent* MonsterStatus = PartyMonsterPawn->GetMonsterStatus();
			if (CurrentSkilldata.IsUseStatusSTR)
			{
				float MonsterStat = MonsterStatus->GetSTR();
				OwnerDamage = CurrentSkilldata.BonusDamage * MonsterStat;
				BaseDamage = CurrentSkilldata.Damage;
			}
			else
			{
				float MonsterStat = MonsterStatus->GetINT();
				OwnerDamage = CurrentSkilldata.BonusDamage * MonsterStat;
				BaseDamage = CurrentSkilldata.Damage;
			}
			
		}
		//base monster
		else 
		{
			ABaseMonster* MonsterPawn = Cast<ABaseMonster>(OwningPawn);
			check(MonsterPawn);
			MonsterSkillComponent = MonsterPawn->GetMonsterSkilRow();
			check(MonsterSkillComponent);
			CurrentSkilldata = MonsterSkillComponent->GetCurrentSkillData();
			ProjectileTableRow = CurrentSkilldata.ProjectileRowHandle.GetRow<FProjectileTableRow>(TEXT("SkillProjectile"));
			check(ProjectileTableRow);

			UStatusComponent* MonsterStatus = MonsterPawn->GetMonsterStatus();
			if (CurrentSkilldata.IsUseStatusSTR)
			{
				float MonsterStat = MonsterStatus->GetSTR();
				OwnerDamage = CurrentSkilldata.BonusDamage * MonsterStat;
				BaseDamage = CurrentSkilldata.Damage;
			}
			else 
			{
				float MonsterStat = MonsterStatus->GetINT();
				OwnerDamage = CurrentSkilldata.BonusDamage * MonsterStat;
				BaseDamage = CurrentSkilldata.Damage;
			}
		}

		UWorld* World = OwningPawn->GetWorld();
		AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileTableRow->ProjectileClass,
			FTransform::Identity, OwningPawn, OwningPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->SetData(CurrentSkilldata.ProjectileRowHandle);
		Projectile->SetStatDamage(BaseDamage, OwnerDamage);

		FTransform NewTransform;
		NewTransform.SetLocation(MuzzleLocation);
		NewTransform.SetRotation(ProjectileRotator.Quaternion());
		Projectile->FinishSpawning(NewTransform);

	}
	


	//UWorld* World = OwningPawn->GetWorld();

}

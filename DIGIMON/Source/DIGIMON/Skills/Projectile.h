// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

USTRUCT()
struct DIGIMON_API FProjectileTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FProjectileTableRow();

public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Projectile|Effect", meta = (RowType = "/Script/Digimon.EffectTableRow"))
	FDataTableRowHandle HitEffectTableRowHandle;

	//Charge 형태의 스킬들 확인
	UPROPERTY(EditAnywhere, Category = "Projectile")
	bool bProjetileCharge ;

	//Charge 시간에 비례해서 스피드값 증가 bChargeTime*speed 
	UPROPERTY(EditAnywhere, Category = "Projectile")
	float bChargeTime;

};

UCLASS()
class DIGIMON_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);

	//Damage 관련은 SkillBase에서 처리할 예정이니 StatusComponent가져올 필요가 없음

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChargeProjectile();

protected:
	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY()
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/Digimon.ProjectileTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FProjectileTableRow* ProjectileData;


	bool IsCharge;
	float fChargeSpeed;

};

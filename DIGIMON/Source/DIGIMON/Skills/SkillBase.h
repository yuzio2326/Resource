// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "SkillBase.generated.h"

USTRUCT()		//나중에
struct DIGIMON_API  FSkillDataRow : public FTableRowBase
{
	GENERATED_BODY()
	FSkillDataRow();

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	float UseMP;		//CanChange
	//Delete 
	//UPROPERTY(EditAnywhere, Category = "Skill")
	//FTransform Transform = FTransform::Identity;
	//Projectile같은 melee만들고 거기서 데미지랑 이펙트 넣고 딜 ㄱㄱ
	UPROPERTY(EditAnywhere, Category = "Skill")
	float Damage;		
	//INT STR 
	UPROPERTY(EditAnywhere, Category = "Skill")
	bool IsUseStatusSTR;		
	//status 기반 추가뎀(계수)
	UPROPERTY(EditAnywhere, Category = "Skill")
	float BonusDamage;		
	//AP = true, AD = false
	UPROPERTY(EditAnywhere, Category = "Skill")
	bool SkillDamageType;				
	//CoolTime
	UPROPERTY(EditAnywhere, Category = "Skill")
	float SkillCoolTime;
	//돌아가는놈 예정
	UPROPERTY(EditAnywhere, Category = "Skill")
	float CurrentSkillCoolTime;
	UPROPERTY(EditAnywhere, Category = "Skill")
	bool IsRanged;

	UPROPERTY(EditAnywhere, Category = "Skill")
	TSubclassOf<ASkillBase> SkillBaseClass;

	//SkillAnim
	//UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	//TSubclassOf<UCustomDioAnimInstance> AnimClass;
	UPROPERTY(EditAnywhere, Category = "SkillAnimation")
	TArray<UAnimMontage*> SkillAnimation;
	//UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	//TArray<UAnimMontage*> HitReactMontage;

	//투사체 형태의 스킬은 해당 요소를 사용하도록 합니다
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.ProjectileTableRow"))
	FDataTableRowHandle ProjectileRowHandle; // 원거리 투사체

};




UCLASS()
class DIGIMON_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

};

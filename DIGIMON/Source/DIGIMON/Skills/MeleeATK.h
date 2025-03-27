// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "MeleeATK.generated.h"

USTRUCT()
struct DIGIMON_API FMeleeATKTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FMeleeATKTableRow();
public:
	UPROPERTY(EditAnywhere, Category = "MeleeATK")
	UCapsuleComponent* CapsuleComponent = nullptr;	//Mat을 alpha 0으로 ㄱㄱ

	UPROPERTY(EditAnywhere, Category = "MeleeATK")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "MeleeATK")
	TSubclassOf<AMeleeATK> MeleeATKClass;

	UPROPERTY(EditAnywhere, Category = "MeleeATK|Effect", meta = (RowType = "/Script/KDT3D.EffectTableRow"))
	FDataTableRowHandle HitEffectTableRowHandle;

	UPROPERTY(EditAnywhere, Category = "MeleeATK | Damage")
	float DMG = 0;

	UPROPERTY(VisibleAnywhere, Category = "MeleeATK | Damage", meta = (RowType = "/Script/DIGIMON.SkillDataRow"))
	FDataTableRowHandle SkillDataTableRowHandle;	//Skill		skill 의 기본 데미지와 사용할 status 타입(INT or STR) 계수 가지고 오고
	UPROPERTY(VisibleAnywhere, Category = "MeleeATK | Damage", meta = (RowType = "/Script/DIGIMON.BasePawnData"))
	FDataTableRowHandle StatusDataTableRowHandle;	//Status	status 기반 위 데미지 계수 기반 BonusDamage 추가하기
	

};

UCLASS()
class DIGIMON_API AMeleeATK : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeATK();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	UCapsuleComponent* MeleeCapsuleComponent;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT3D.MeleeATKTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	FMeleeATKTableRow* MeleeATKData;
};

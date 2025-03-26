// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Skills/SkillBase.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

USTRUCT()	//Skill관리용
struct DIGIMON_API FSkillTableRow : public FTableRowBase
{
	GENERATED_BODY()
public: // Skill
	UPROPERTY(EditAnywhere, Category = "Skill", meta = (RowType = "/Script/DIGIMON.SkillDataRow"))
	TArray<FDataTableRowHandle> SkillArray;	//FSkillDataRow = skillbase쪽에 있는 데이터 가지고 와서 설정

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUsingSkill, bool, UsingSkill, bool, CanUseSkill);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	void SetData(FDataTableRowHandle InDataTableRowHandle);
	void InitializeSkillData(UDataTable* SkillDataTable);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.SkillTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill Data")
	FSkillTableRow SkillTableRow;
protected:
	USkeletalMeshComponent* SkeletalMeshComponent;
	UAnimInstance* AnimInstance;
	//UAdvanceFloatingPawnMovement* MovementComponent;//ADD Movement

protected:
	//Monster SkillComponent가 아닌 이걸로 설정
	bool bIsMonster;

	TArray<float> SkillCooldowns;

	UPROPERTY(BlueprintAssignable)
	FOnUsingSkill OnUsingSkill;
};

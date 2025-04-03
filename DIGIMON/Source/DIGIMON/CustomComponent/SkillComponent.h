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
	//FSkillDataRow = skillbase쪽에 있는 데이터 가지고 와서 설정 
	// mp랑 dmg전부 그쪽에 있고 얘는 그냥 해당 몬스터가 가지고있는 스킬 Array임
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (RowType = "/Script/DIGIMON.SkillDataRow"))
	//TArray<FDataTableRowHandle> SkillArray;	

	//얘가 더 ㄱㅊ긴 함... 위는 좀 2중 3중으로 돌려 쓰는 느낌? 
	//data 다 옮기고 위에 없애기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (RowType = "/Script/DIGIMON.SkillDataRow"))
	TArray<FSkillDataRow> SkillDataArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill", meta = (RowType = "/Script/DIGIMON.SkillDataRow"))
	TArray<FSkillDataRow> RangedSkillArray;


};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUsingSkill, bool, UsingSkill, bool, CanUseSkill, bool, IsRangeSkill);


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

	void CanUseSkill();
	//AI 가 사용할 useSkill
	void AIUseSkill(int IndexSkill);

	//void UseRangedSkill();

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
	
	//AI Use Skills 
	bool bIsAI = false;

	bool ISAllSkillCooltime = false;
	bool ISRangedSkillCooltime = false;
	bool ISMeleeSkillCooltime = false;
	bool UsingSkill = false;


	TArray<float> SkillCooldowns;
	TArray<float> RangedSkillCooldowns;



	bool bIsUsingSkill = false;



	UPROPERTY(BlueprintAssignable)
	FOnUsingSkill OnUsingSkill;


};

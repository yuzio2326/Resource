// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Animation/BaisicCharacterAnimInstance.h"

//#include "Ba"
#include "../PawnAnimInstance.h"

#include "SkillComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


USTRUCT()
struct DIGIMON_API FPawnTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	FTransform MeshTransform = FTransform::Identity;

	//UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	//TSubclassOf<UBaisicCharacterAnimInstance> AnimClass;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	void StatusSetting(int SetLevel, float SetEXP,float SetMaxHP, float SetMaxMP, float SetSTR, float SetSTR_DEF, float SetINT, float SetINT_DEF, int SetPawnType) 
	{Level = SetLevel, EXP = SetEXP, MaxHP = SetMaxHP, HP = SetMaxHP, MaxMP = SetMaxMP, MP = SetMaxMP, STR = SetSTR, STRDEF = SetSTR_DEF, INT = SetINT, INTDEF = SetINT_DEF, Type = SetPawnType;}

protected:
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	void LevelUp();
	bool KillEnemy();


protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.BasePawnData"))//만들어야함
	FDataTableRowHandle DataTableRowHandle;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* MonsterSkillComponent;


protected:
	//Add UPROPERTY(VisibleAnywhere) For Visable In UE
	UPROPERTY(VisibleAnywhere)
	int Level;
	UPROPERTY(VisibleAnywhere)
	int Type;
	UPROPERTY(VisibleAnywhere)
	float MaxHP;
	UPROPERTY(VisibleAnywhere)
	float HP;
	UPROPERTY(VisibleAnywhere)
	float MaxMP;	//마나 역할
	UPROPERTY(VisibleAnywhere)
	float MP;
	UPROPERTY(VisibleAnywhere)
	float MaxEXP;
	UPROPERTY(VisibleAnywhere)
	float EXP;		//Monster의 경우 주는 경험치 양
	UPROPERTY(VisibleAnywhere)
	float STR;
	UPROPERTY(VisibleAnywhere)
	float INT;
	UPROPERTY(VisibleAnywhere)
	float STRDEF;
	UPROPERTY(VisibleAnywhere)
	float INTDEF;



	float MainSTR;		//STR, HP_GENERATION
	float MainINT;		//INT, MP_GENERATION
	float MainHealth;	//HP, HP_Generation
	float MainPatient;	//DEF, MP_GENERATION




		
};

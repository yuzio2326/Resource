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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChanged, float, CurrentHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMPChanged, float, CurrentMP, float, MaxMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEXPChanged, float, CurrentEXP, float, MaxEXPLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStatusChanged, float, Strength, float, Intelligence, float, ADDefence, float, APDefence);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

	void StatusSetting(int SetLevel, float SetEXP,float SetMaxHP, float SetMaxMP, float SetSTR, float SetSTR_DEF, float SetINT, float SetINT_DEF, int SetPawnType) 
	{Level = SetLevel, EXP = SetEXP, MaxEXP = (SetLevel * 20) + (SetLevel * (5 * SetLevel)), MaxHP = SetMaxHP, HP = SetMaxHP, MaxMP = SetMaxMP, MP = SetMaxMP, STR = SetSTR, STRDEF = SetSTR_DEF, INT = SetINT, INTDEF = SetINT_DEF, Type = SetPawnType;}

	bool CanMove() const { return !bDie; }
	bool IsDie() const { return bDie; }
	float GetHP() const { return HP; }
	float GetMP() const { return MP; }
	float GetMaxMP() const { return MaxMP; }
	float GetMaxHP() const { return MaxHP; }
	float GetSTR() const { return STR; }
	float GetINT() const { return INT; }
	float GetEXP() const { return EXP; }
	void AddEXP(float fGetEXP);

	void AddHP(float Damage);
	void AddMP(float SpendMP);


	int GetOwnerPawnType() const { return OwnerPawnType; }
	AController* GetLastInstigator() const { return LastInstigator; }

	void Attack(bool InAttacking) { bAttack = InAttacking; }
	bool GetAttack() const { return bAttack; }
protected:
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

public:
	void LevelUp();
	bool KillEnemy();	//OnDie 에서 전부 해결 할까?


protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.BasePawnData"))
	FDataTableRowHandle DataTableRowHandle;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* MonsterSkillComponent;


protected:
	//Add UPROPERTY(VisibleAnywhere) For Visable In UE
	UPROPERTY(BlueprintReadOnly)
	int Level;
	// 1유년기 2 성장기 3성숙기 4완전체 5 궁극체
	UPROPERTY(BlueprintReadOnly)
	int EvolutionType;
	// 1 Virus 2 data 3 vaccine 
	UPROPERTY(BlueprintReadOnly)
	int Type;
	UPROPERTY(BlueprintReadOnly)
	float MaxHP;
	UPROPERTY(BlueprintReadOnly)
	float HP;
	UPROPERTY(BlueprintReadOnly)
	float MaxMP;	//마나 역할
	UPROPERTY(BlueprintReadOnly)
	float MP;
	UPROPERTY(BlueprintReadOnly)
	float MaxEXP;
	UPROPERTY(BlueprintReadOnly)
	float EXP;		//Monster의 경우 주는 경험치 양
	UPROPERTY(BlueprintReadOnly)
	float STR;
	UPROPERTY(BlueprintReadOnly)
	float INT;
	UPROPERTY(BlueprintReadOnly)
	float STRDEF;
	UPROPERTY(BlueprintReadOnly)
	float INTDEF;
	UPROPERTY(BlueprintReadOnly)
	float OwnerDamage;	//사용한 스킬 및 공격 가지고 와서 damage세팅한뒤 해당하는 damage변수를 자꾸 바꾸기 이후 damage를 가지고 스킬 데미지 입히는 방향 ㄱㄱ

	//Monster Or PartyMonster Or Player
	UPROPERTY(BlueprintReadOnly)
	int OwnerPawnType;



	float MainSTR;		//STR, HP_GENERATION
	float MainINT;		//INT, MP_GENERATION
	float MainHealth;	//HP, HP_Generation
	float MainPatient;	//DEF, MP_GENERATION

	bool bAttack = false;
	bool bDie = false;
	bool bZoom = false;

public:
	AController* LastInstigator = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnHPChanged OnHPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnMPChanged OnMPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnEXPChanged OnEXPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnLevelChanged OnLevelChanged;
	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged OnStatusChanged;
	FOnDie OnDie;
		
};

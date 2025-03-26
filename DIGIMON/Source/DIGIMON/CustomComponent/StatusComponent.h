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
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.PawnTableRow"))//만들어야함
	FDataTableRowHandle DataTableRowHandle;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* MonsterSkillComponent;


protected:
	int Level;
	float MaxHP;
	float HP;
	float MaxMP;	//마나 역할
	float MP;
	float MaxEXP;
	float EXP;		//Monster의 경우 주는 경험치 양
	float AD;
	float AP;


	float MainSTR;
	float MainINT;
	float MainDEX;
	float MainLUK;




		
};

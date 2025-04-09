// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "../Data/PawnData.h"
#include "../Misc/Utils.h"
#include "../CustomComponent/AdvanceFloatingPawnMovement.h"
//#include "Engine/"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMonster.generated.h"

USTRUCT()
struct DIGIMON_API FBaseMonsterTableRow : public FBasePawnData
{
	GENERATED_BODY()

public:
	//DropItem
	//UPROPERTY(EditAnywhere, Category = "DropItem", meta = (RowType = "/Script/KDT3D.ItemPackTableRow"))
	//FDataTableRowHandle DropItem;
	
	//특수 객체 만들기 힘들다는 단점이 있긴함...
	//UPROPERTY(EditAnywhere, Category = "DropItem", meta = (RowType = "/Script/DIGIMON.PawnTableRow"))
	//FDataTableRowHandle BasePawnData;

	bool BossVision = false;//인식 범위 넓히기용
};



UCLASS()
class DIGIMON_API ABaseMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseMonster();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetSkillData(const FDataTableRowHandle& InSkillDataTableRowHandle);
protected:
	//Duplacte In Editor
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;

protected:
	/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized, only called during gameplay */
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);
protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
	UFUNCTION()
	virtual void OnDie();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USkillComponent* GetMonsterSkilRow() const { return SkillComponent; }


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;

	FBaseMonsterTableRow* MonsterData;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/Digimon.BaseMonsterTableRow"))
	FDataTableRowHandle MonsterDataTableRowHandle;

	FSkillTableRow* MonsterSkillData;

	UAnimMontage* CurrentDieMontage;

protected:
	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.BaseMonsterTableRow"))
	//FDataTableRowHandle BaseMonsterDataTableRowHandle;

	UPROPERTY(VisibleAnywhere)
	UAdvanceFloatingPawnMovement* MovementComponent;
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* AISenseConfig_Sight;
	UPROPERTY(VisibleAnywhere)
	UAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;

	//const FBasePawnData* PawnDataTableRow = nullptr;


public:
	// false 면 Monster true 면 Player Party Monster
	UPROPERTY(BlueprintReadOnly)
	bool bOwningPlayer;	




};

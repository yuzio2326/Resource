// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Data/PawnData.h"
#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
<<<<<<< HEAD
#include "Components/CapsuleComponent.h"
=======
//#include "Engine/"
#include "CapsuleComponent.generated.h"
>>>>>>> cb52730353b82fd9bfed43b7a48dfc9299d1b050

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMonster.generated.h"
USTRUCT()
struct DIGIMON_API FBaseMonsterTableRow : public FBasePawnData
{
	GENERATED_BODY()

public:
	//나중에 DropTable 추가 이후 사용할 예정
	UPROPERTY(EditAnywhere, Category = "DropItem", meta = (RowType = "/Script/DIGIMON.ItemPackTableRow"))
	FDataTableRowHandle DropItem;

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
protected:
	//base Pawn data table 만들어서 해당 데이터 참고 해가지구 player와 monster모두 사용 가능하게 함
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.PawnTableRow"))
	FDataTableRowHandle BasePawnDataTableRowHandle;

	FBaseMonsterTableRow* MonsterData;


protected:
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;


};

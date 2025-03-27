// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "../Data/PawnData.h"
//#include "Engine/"

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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;

	FBaseMonsterTableRow* MonsterData;

protected:
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.PawnTableRow"))
	FDataTableRowHandle BasePawnDataTableRowHandle;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "Components/CapsuleComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMonster.generated.h"

USTRUCT()		//나중에
struct DIGIMON_API  FBasePawnData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Pawn")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	FTransform MeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TSubclassOf<UPawnAnimInstance> AnimClass;

public:
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 44.f;

public: // Animation
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> HitReactMontage;
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> DieMontage;
	//Can Control Anim
	UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	TArray<UAnimMontage*> AttackMontage;

	//UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	//TArray<UAnimMontage*> DashMontage;
	//UPROPERTY(EditAnywhere, Category = "Pawn|Animation")
	//TArray<UAnimMontage*> SkillMontage;

	UPROPERTY(EditAnywhere, Category = "Pawn|Skill", meta = (RowType = "/Script/DIGIMON.SkillTableRow"))
	FDataTableRowHandle OwnSkillData;


public: // Movement
	UPROPERTY(EditAnywhere, Category = "Pawn|Movement")
	float MovementMaxSpeed = 400.f;

public: // AI (Enemy만 적용)
	//UPROPERTY(EditAnywhere, Category = "Pawn|AI")
	//TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float HP = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float STR = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float STR_DEF = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float INT = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float INT_DEF = 0;
	//UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	//float DMG = 0;


	/*UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	TArray<float> SkillDMGArray;*/
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


protected:
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;
	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;


};

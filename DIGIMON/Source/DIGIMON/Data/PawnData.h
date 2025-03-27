// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"



#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnData.generated.h"


USTRUCT()		//Base PawnData 
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
<<<<<<< HEAD
	//Make Base Capsule
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	TSubclassOf<UShapeComponent> CollisionClass = UCapsuleComponent::StaticClass();
	//유년기 다수 사용 가능
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionSphereRadius = 32.f;
	// 안쓸수도?
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 50.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 100.f;
=======
	//UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	//TSubclassOf<UShapeComponent> CollisionClass = USphereComponent::StaticClass();
	//UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	//float CollisionSphereRadius = 32.f;
	//UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	//FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 22.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 44.f;
>>>>>>> cb52730353b82fd9bfed43b7a48dfc9299d1b050

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
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	int PawnType = 0;	// Data =1 / Virus=2 / Vaccine=3

	//UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	//float DMG = 0;


	/*UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	TArray<float> SkillDMGArray;*/
};


UCLASS()
class DIGIMON_API APawnData : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

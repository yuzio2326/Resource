#pragma once

#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
//#include "../Misc/Utils.h"
#include "Aicontroller.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnData.generated.h"



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
	//Make Base Capsule
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	TSubclassOf<UShapeComponent> CollisionClass = UCapsuleComponent::StaticClass();
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionSphereRadius = 32.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	FVector CollisionBoxExtent = FVector(32.0, 32.0, 32.0);

	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleRadius = 50.f;
	UPROPERTY(EditAnywhere, Category = "Pawn|Collision")
	float CollisionCapsuleHalfHeight = 100.f;

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

public: // AI (Monster 및 Party에 적용)
	UPROPERTY(EditAnywhere, Category = "Pawn|AI")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	int Level = 1;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float EXP = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float HP = 0;
	UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	float MP = 0;
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

	//Use DMG In Status
	//UPROPERTY(EditAnywhere, Category = "Pawn|Status")
	//float DMG = 0;

	//Each of Skill have Own Damage and will Change Status
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
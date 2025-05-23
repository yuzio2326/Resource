// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "CustomComponent/SoftWheelSpringArmComponent.h"
#include "PaperSpriteComponent.h"
#include "CustomComponent/WeaponChildActorComponent.h"
#include "PawnAnimInstance.h"
#include "CustomComponent/StatusComponent.h"
#include "CustomComponent/InventoryComponent.h"
#include "CustomComponent/SkillComponent.h"
#include "Misc/Utils.h"
#include "Data/PawnData.h"
#include "BasePlayer.generated.h"

USTRUCT()
struct DIGIMON_API FBasePlayerData : public FBasePawnData 
{
	GENERATED_BODY()
public:
	// 기본 무기
	UPROPERTY(EditAnywhere, Category = "SkillProjectile", meta = (RowType = "/Script/DIGIMON.WeaponTableRow"))
	FDataTableRowHandle WeaponRowHandle; 
	//아이템에서 계속 바꿀 예정


};

UCLASS()
class DIGIMON_API ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnDie();
	UFUNCTION(BlueprintCallable)
	virtual void Attack();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual bool CanJumpInternal_Implementation() const override;
protected:
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetInventoryData(const FDataTableRowHandle& InDataTableRowHandle);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateDesiredAimRotation(const float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
	UStatusComponent* GetStatusComponent() { return StatusComponent; }

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USoftWheelSpringArmComponent> SpringArm;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponChildActorComponent> Weapon;

	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;

	UPROPERTY(VisibleAnywhere)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* MinimapSpriteComponent;

	UPawnAnimInstance* AnimInstance;

	UAnimMontage* CurrentDieMontage;
	
	FRotator DesiredAimRotation;

	FSkillTableRow* RowSkill;

protected:
	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT3D.PawnTableRow"))
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.BasePawnData"))
	FDataTableRowHandle DataTableRowHandle;

	FBasePawnData* CharacterData;


	bool IsZoom = false;
};

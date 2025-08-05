// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ABaseWeapon;
class UPawnAnimInstance;
USTRUCT()
struct DIGIMON_API FWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FWeaponTableRow();
public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

	//Static, Skeletalmesh 선택
	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* StaticMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FTransform Transform = FTransform::Identity;
	//Use Int Or STR
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool WeaponTypeAP;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	float WeaponDamage;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.ProjectileTableRow"))
	FDataTableRowHandle ProjectileRowHandle;
	
	// Weapon Anim Parts -> Animation	무기마다 다른 Animation 작동
public:
	// Make To Change Attack Animation To change Upper Body Or Other 
	UPROPERTY(EditAnywhere, Category = "Weapon | Animation")
	TSubclassOf<UPawnAnimInstance> AnimClass;

	// Add Attack Montage in here;
	UPROPERTY(EditAnywhere, Category = "Weapon | Animation")
	TArray<UAnimMontage*> WeaponAttackMontage;

	// if Target GetDamage From This Weapon
	UPROPERTY(EditAnywhere, Category = "Enemy | Animation")
	TArray<UAnimMontage*> HitReactMontage;

};

UCLASS()
class DIGIMON_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
protected:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.WeaponTableRow"))
	FDataTableRowHandle DataTableRowHandle;
	const FWeaponTableRow* WeaponTableRow = nullptr;

	UPawnAnimInstance* BaseAnimInstance = nullptr;

protected:
	APawn* OwningPawn = nullptr;

};

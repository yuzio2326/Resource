// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class ABaseWeapon;
USTRUCT()
struct DIGIMON_API FWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FWeaponTableRow();
public:
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FTransform Transform = FTransform::Identity;

};

UCLASS()
class DIGIMON_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

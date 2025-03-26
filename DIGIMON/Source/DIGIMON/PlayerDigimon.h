// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerDigimon.generated.h"

UCLASS()
class DIGIMON_API APlayerDigimon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerDigimon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT3D.PawnTableRow"))
	FDataTableRowHandle DataTableRowHandle;


};

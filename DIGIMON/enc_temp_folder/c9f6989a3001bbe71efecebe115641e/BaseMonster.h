// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../CustomComponent/StatusComponent.h"
#include "../CustomComponent/SkillComponent.h"
#include "Components/CapsuleComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseMonster.generated.h"



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

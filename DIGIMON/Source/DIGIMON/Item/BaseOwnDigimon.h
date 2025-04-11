// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/PawnData.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseOwnDigimon.generated.h"

USTRUCT()
struct DIGIMON_API FOwnDigimonTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	//SaveGame Class로 저장하고 불러올수 있도록 한다

	UPROPERTY(EditAnywhere, Category = "Projectile|Effect", meta = (RowType = "/Script/Digimon.BasePawnData"))
	FDataTableRowHandle HitEffectTableRowHandle;


};

UCLASS()
class DIGIMON_API ABaseOwnDigimon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseOwnDigimon();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnOwnMonster();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/Digimon.BasePawnData"))
	FDataTableRowHandle DataTableRowHandle;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

USTRUCT()
struct DIGIMON_API FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FItemTableRow();
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<ABaseItem> ItemClass;

	// 0 weapon 1 usable 2 digimon 3 Other(기타템)
	UPROPERTY(EditAnywhere, Category = "Item")
	int itemtype = 0;


};

UCLASS()
class DIGIMON_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

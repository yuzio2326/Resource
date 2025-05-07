// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BaseItem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUsableItem.generated.h"

class ABaseUsableItem;

USTRUCT()
struct DIGIMON_API FUsableItem : public FTableRowBase
{
	GENERATED_BODY()
	FUsableItem();
public:
	UPROPERTY(EditAnywhere, Category = "Item | Usage")
	TSubclassOf<ABaseUsableItem> ItemClass;
	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* StaticMesh = nullptr;
	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item")
	FVector Scale = FVector(2.0, 2.0, 2.0);
	//max size =255
	UPROPERTY(EditAnywhere, Category = "Item | Usage")
	uint8 ItemStack = 0;
	// 1=Heal 2=DMGUP 3=DmgRegist
	UPROPERTY(EditAnywhere, Category = "Item | Usage")
	uint8 UsageType=0;
	//BasePower
	UPROPERTY(EditAnywhere, Category = "Item | Usage")
	uint8 UsagePower=0;
	//PercentPower
	UPROPERTY(EditAnywhere, Category = "Item | Usage")
	uint8 UsagePowerPercent=0;
	
	

};

UCLASS()
class DIGIMON_API ABaseUsableItem : public AActor
{
	GENERATED_BODY()

public:
	struct FItemContext
	{
		//item 가지고 있는 대상
		ABasePlayer* OwnerPlayer;

		//item 사용 대상
		APawn* TargetPawn;

	};
	
public:	
	// Sets default values for this actor's properties
	ABaseUsableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetData();
	void UseItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




protected:
	FUsableItem UsableItemData;


};

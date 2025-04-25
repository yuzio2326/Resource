// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

//고민중... 그냥 아이템 종류별로 만들어 놓고 얘는 쓰지 말까?
USTRUCT()
struct DIGIMON_API FItemTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FItemTableRow();
public:
	//필요할까?
	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<ABaseItem> ItemClass;

	// 0 weapon 1 usable 2 digimon 3 Other(기타템)
	UPROPERTY(EditAnywhere, Category = "Item")
	int itemtype = 0;

	//count item number
	UPROPERTY(EditAnywhere, Category = "Item")
	int itemNum = 0;

	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* StaticMesh = nullptr;
	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item")
	FVector Scale = FVector(2.0, 2.0, 2.0);



};

class USceneCaptureComponent2D;

UCLASS()
class DIGIMON_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	//setting preview
	void SetWeaponMesh(UStaticMesh* NewMesh);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
    USceneCaptureComponent2D* SceneCapture;

	UPROPERTY()
    UStaticMeshComponent* ItemMesh;


};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
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

	/*
		Usable=0, Other, EquipWeapon, EquipArmor, EquipHelm, EquipCapsule, EquipCrest, Partner
	*/ 
	UPROPERTY(EditAnywhere, Category = "Item")
	uint8 Itemtype = 0;
	UPROPERTY(EditAnywhere, Category = "Item")
	uint8 itemID = 0;
	//Stack 가능한 타입인지 bool 로 ㄱㄱ
	UPROPERTY(EditAnywhere, Category = "Item")
	bool Stackable = false;
	//count item number
	UPROPERTY(EditAnywhere, Category = "Item")
	uint8 itemStack = 0;
	//inventory 에서 보여줄 texture 2d
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* Thumnail;
	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	UStaticMesh* StaticMesh = nullptr;
	// Skeletal 은 사라질수도 있음
	// SkeletalMesh 또는 StaticMesh를 선택하면 둘 중 유요한 하나를 사용해서 Mesh로 띄워준다
	UPROPERTY(EditAnywhere, Category = "Item")
	USkeletalMesh* SkeletalMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Item")
	FVector Scale = FVector(2.0, 2.0, 2.0);
	UPROPERTY(EditAnywhere, Category = "Item")
	FTransform Transform = FTransform::Identity;
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

	//Using Sound
	UPROPERTY(EditAnywhere, Category = "Item")
	TObjectPtr<USoundBase> Sound;
	UPROPERTY(EditAnywhere, Category = "Item|Sound")
	float VolumeMultiplier = 1.f;


};

class USceneCaptureComponent2D;

UCLASS()
class DIGIMON_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void UseItem(APawn* Pawn);

	//setting preview
	void SetWeaponMesh(UStaticMesh* NewMesh);


protected:
	void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
    USceneCaptureComponent2D* SceneCapture;

	UPROPERTY()
    UStaticMeshComponent* ItemMesh;
	UPROPERTY(VisibleAnywhere)
	UShapeComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/DIGIMON.ItemTableRow"))
	FDataTableRowHandle DataTableRowHandle;
	UPROPERTY()
	FItemTableRow ItemTable;
	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;
};

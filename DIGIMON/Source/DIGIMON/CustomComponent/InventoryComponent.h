// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenInventory, bool, IsOpenInventory);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGIMON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 인벤 열리고 닫히는거 아이템 사용, 이동(드래그 드롭)
	UFUNCTION(BlueprintCallable)
	void OpenInventory(bool OpeningInventory);

public:
	//UI 쪽에서 button action으로 해당 값을 바꾸도록 하고 해당 값에 따라서 visable을 바꾸도록 한다.
	UPROPERTY(EditAnywhere)
	bool IsOpenInventory = false;

	UPROPERTY(BlueprintAssignable)
	FOpenInventory	OnInventory;


};

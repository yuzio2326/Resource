// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponent/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}

void UInventoryComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	//For문 돌려서 가지고 있는 모든 아이템 순회할 예정
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FItemTableRow* Data = DataTableRowHandle.GetRow<FItemTableRow>(TEXT("ItemTableRow"));
	if (!Data) { ensure(false); return; }




}

void UInventoryComponent::OpenInventory(bool OpeningInventory)
{
	//OnInventory.Broadcast(OpeningInventory);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::UseItem()
{

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"


// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatusComponent::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	//FPawnTableRow* CharacterData = DataTableRowHandle.GetRow<FPawnTableRow>(TEXT("Character"));
	HP = MaxHP;

}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (EXP >= MaxEXP)
	{
		LevelUp();
	}

	// ...
}

void UStatusComponent::LevelUp()
{
	if (EXP >= MaxEXP)
	{

	}
	else { return; }



	return ;
}

bool UStatusComponent::KillEnemy()
{


	return false;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USkillComponent::SetData(FDataTableRowHandle InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FSkillTableRow* Data = DataTableRowHandle.GetRow<FSkillTableRow>(TEXT("SkillTableRow"));
	if (!Data) { ensure(false); return; }
	SkillTableRow = *Data;

	//Owner 정보 빼오고
	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	AnimInstance = SkeletalMeshComponent->GetAnimInstance();

	SkillCooldowns.SetNum(SkillTableRow.SkillArray.Num());
	for (int32 i = 0; i < SkillTableRow.SkillArray.Num() - 1; i++)
	{
		SkillCooldowns[i] = 0.0f;
	}
	if (SkillTableRow.SkillArray.Num() > 0)
		OnUsingSkill.Broadcast(false, true);
	else
		OnUsingSkill.Broadcast(false, true);




}

void USkillComponent::InitializeSkillData(UDataTable* SkillDataTable)
{
	if (!SkillDataTable) return;

	static const FString ContextString(TEXT("Skill Data Context"));
	TArray<FSkillDataRow*> AllSkillData;
	SkillDataTable->GetAllRows<FSkillDataRow>(ContextString, AllSkillData);

	for (FSkillDataRow* SkillData : AllSkillData)
	{
		if (SkillData)
		{
			// 필요한 데이터만 저장하거나, 초기화합니다.
			//SkillDataArray.Add(*SkillData);
		}
	}
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


}


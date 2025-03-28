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

	SkillCooldowns.SetNum(SkillTableRow.SkillDataArray.Num());
	for (int32 i = 0; i < SkillTableRow.SkillDataArray.Num() - 1; i++)
	{
		SkillCooldowns[i] = 0.0f;
	}
	if (SkillTableRow.SkillDataArray.Num() > 0)
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

void USkillComponent::CanUseSkill()
{
	//skill data의 cooltime을 비교 하면서 사용 가능한지 아닌지 여기서 확인하고 useSkill을 사용합니다.
}

void USkillComponent::UseSkill(int IndexSkill)
{
	//자신이 사용할 skill의 데이터를 가지고 와서 status에 세팅을 하고 해당 스킬이 끝나면 다시 돌려줍니다.

	if (SkillTableRow.SkillDataArray.IsEmpty()) { return; }

	FSkillDataRow SkillData = SkillTableRow.SkillDataArray[IndexSkill];





}


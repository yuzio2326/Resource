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

	//SkillCooldowns.SetNum(SkillTableRow.SkillDataArray.Num());
	
	//원거리 근거리 스킬 저장 방식을 나눴음


	int32 OwnSkillNum = SkillTableRow.SkillDataArray.Num();
	int32 RangeSkillNum = SkillTableRow.RangedSkillArray.Num();

	// 원거리 근거리 스킬 쿨타임 적용
	SkillCooldowns.SetNum(OwnSkillNum);
	for (int32 i = 0; i < OwnSkillNum; i++)
	{
		SkillCooldowns[i] = 0.0f;
	}
	RangedSkillCooldowns.SetNum(RangeSkillNum);
	for (int32 i = 0; i < RangeSkillNum; i++)
	{
		RangedSkillCooldowns[i] = 0.0f;
	}

	//원거리 스킬 관련 broadcast
	if (SkillTableRow.RangedSkillArray.Num() > 0)
		OnUsingSkill.Broadcast(false, true, true);
	else
		OnUsingSkill.Broadcast(false, true, false);

}

void USkillComponent::InitializeSkillData(UDataTable* SkillDataTable)
{
	if (!SkillDataTable) return;

	static const FString ContextString(TEXT("Skill Data Context"));
	TArray<FSkillDataRow*> AllSkillData;
	SkillDataTable->GetAllRows<FSkillDataRow>(ContextString, AllSkillData);

	
}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//Monster의 경우 순환하는 구조로 사용 가능한 스킬이 하나라도 있을 경우 해당 스킬을 사용하도록 한다.
	//원거리 스킬 저장용
	int32 RangedSkillNum = SkillTableRow.RangedSkillArray.Num();
	//근거리 스킬 저장용
	int32 MeleeSkillNum = SkillTableRow.SkillDataArray.Num();

	//MeleeSkill이 있으면
	if (MeleeSkillNum > 0)
	{
		//TODO:: BroadCast로 ISAllSkillCooltime얘가 모두 쿨이면 사용 가능 여부를 false로 ㄱㄱ
		for (int32 i = 0; i < MeleeSkillNum; i++)
		{
			//단 하나라도 쿨타임이 다 돌았으면 false
			if (SkillCooldowns[i] <= 0)
			{
				ISMeleeSkillCooltime = false;
				break;
			}
			else { ISMeleeSkillCooltime = true; }
		}
		for (int32 i = 0; i < MeleeSkillNum; i++) {
			if (SkillCooldowns[i] > 0.0f) {
				SkillCooldowns[i] -= DeltaTime;
				SkillCooldowns[i] = FMath::Max(SkillCooldowns[i], 0.0f);  // 0보다 작아지지 않도록
			}
		}

	}
	else { ISMeleeSkillCooltime = true; }

	//Ranged Skill 이 있으면
	if (RangedSkillNum > 0)
	{
		//모든 스킬 쿨타임인지 아는 bool의 기본값을 true로
		for (int32 i = 0; i < RangedSkillNum; i++)
		{
			//단 하나라도 쿨타임이 다 돌았으면 false
			if (RangedSkillCooldowns[i] <= 0)
			{
				ISRangedSkillCooltime = false;
				break;
			}
			else { ISRangedSkillCooltime = true; }
		}
		for (int32 i = 0; i < RangedSkillNum; i++) {
			if (RangedSkillCooldowns[i] > 0.0f) {
				RangedSkillCooldowns[i] -= DeltaTime;
				RangedSkillCooldowns[i] = FMath::Max(RangedSkillCooldowns[i], 0.0f);  // 0보다 작아지지 않도록
			}
		}

	}
	else { ISRangedSkillCooltime = true; }

	//melee나 range둘중에 하나라도 쿨타임이 돌면
	if (!ISRangedSkillCooltime)
		OnUsingSkill.Broadcast(UsingSkill, true, true);
	else if (!ISMeleeSkillCooltime)
		OnUsingSkill.Broadcast(UsingSkill, true, false);




}

void USkillComponent::UseSkill()
{
	//skill data의 cooltime을 비교 하면서 사용 가능한지 아닌지 여기서 확인하고 useSkill을 사용합니다.
	
	bool CanUseSkill = true;

	//Skill 사용중이 아니면
	if (!bIsUsingSkill) 
	{ 
		int32 SkillNum = SkillTableRow.SkillDataArray.Num();
		//skill 갯수 부족으로 false로 
		if (SkillNum <= 0)
		{
			CanUseSkill = false;
			OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, true);
			return;
		}
		//bIsAI로 monster가 해당 컴포넌트 보유 중이면 랜덤하게 뽑아서 사용하도록 합니다.
		while (!ISMeleeSkillCooltime)
		{
			//Random 뽑고
			int64 Index = FMath::RandRange(0, SkillNum - 1);
			//쿨타임이면 다시 뽑고
			if (SkillCooldowns[Index] > 0) { continue; }
			//아니면 해당 스킬 선택
			else
			{
				ChosenSkillNum = Index;
				break;
			}

		}
		//스킬 모두 쿨타임이면
		if (ISMeleeSkillCooltime && ISRangedSkillCooltime)
		{
			UsingSkill = false;
			CanUseSkill = false;
		}
		else
		{
			UsingSkill = true;
			CanUseSkill = false;
		}
		OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);
		
	}
	//skill 사용중이면
	else 
	{
		FSkillDataRow CurrentSkillMontage = SkillTableRow.SkillDataArray[ChosenSkillNum];
		
		//skill 쿨타임이 적용된 상태면
		if (SkillCooldowns[ChosenSkillNum] > 0)
		{
			//몽타주 재생 완료후
			if (!AnimInstance->Montage_IsPlaying(nullptr))
			{
				//다른 스킬 사용 가능하게 풀어줌
				CanUseSkill = true;
				OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);

			}
		}
		//skill 사용하려고 할때
		else 
		{
			//몽타주 재생중이 아니면 재생 시키도록 ㄱㄱ
			if (!AnimInstance->Montage_IsPlaying(nullptr))
			{
				AnimInstance->Montage_Play(CurrentSkillMontage.SkillAnimation[0]);
				CanUseSkill = false;
				//스킬 사용중이고 스킬 애니메이션 다 안돌았음
				OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);
				//몽타주 애니메이션 재생하면 쿨타임 돌도록 하고
				SkillCooldowns[ChosenSkillNum] = CurrentSkillMontage.SkillCoolTime;
			}


		}
	}

}

void USkillComponent::UseRangeSkill()
{
	//skill data의 cooltime을 비교 하면서 사용 가능한지 아닌지 여기서 확인하고 useSkill을 사용합니다.
	
	bool CanUseSkill = true;

	//Skill 사용중이 아니면
	if (!bIsUsingSkill) 
	{ 
		int32 SkillNum = SkillTableRow.RangedSkillArray.Num();
		//skill 갯수 부족으로 false로 
		if (SkillNum <= 0)
		{
			CanUseSkill = false;
			OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, true);
			return;
		}
		//bIsAI로 monster가 해당 컴포넌트 보유 중이면 랜덤하게 뽑아서 사용하도록 합니다.
		while (!ISMeleeSkillCooltime)
		{
			//Random 뽑고
			int64 Index = FMath::RandRange(0, SkillNum - 1);
			//쿨타임이면 다시 뽑고
			if (SkillCooldowns[Index] > 0) { continue; }
			//아니면 해당 스킬 선택
			else
			{
				ChosenSkillNum = Index;
				break;
			}

		}
		//스킬 모두 쿨타임이면
		if (ISMeleeSkillCooltime && ISRangedSkillCooltime)
		{
			UsingSkill = false;
			CanUseSkill = false;
		}
		else
		{
			UsingSkill = true;
			CanUseSkill = false;
		}
		OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);
		
	}
	//skill 사용중이면
	else 
	{
		FSkillDataRow CurrentSkillMontage = SkillTableRow.RangedSkillArray[ChosenSkillNum];
		
		//skill 쿨타임이 적용된 상태면
		if (SkillCooldowns[ChosenSkillNum] > 0)
		{
			//몽타주 재생 완료후
			if (!AnimInstance->Montage_IsPlaying(nullptr))
			{
				//다른 스킬 사용 가능하게 풀어줌
				CanUseSkill = true;
				OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);

			}
		}
		//skill 사용하려고 할때
		else 
		{
			//몽타주 재생중이 아니면 재생 시키도록 ㄱㄱ
			if (!AnimInstance->Montage_IsPlaying(nullptr))
			{
				AnimInstance->Montage_Play(CurrentSkillMontage.SkillAnimation[0]);
				CanUseSkill = false;
				//스킬 사용중이고 스킬 애니메이션 다 안돌았음
				OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, false);
				//몽타주 애니메이션 재생하면 쿨타임 돌도록 하고
				SkillCooldowns[ChosenSkillNum] = CurrentSkillMontage.SkillCoolTime;
			}


		}
	}
}

void USkillComponent::AIUseSkill(int IndexSkill)
{
	//자신이 사용할 skill의 데이터를 가지고 와서 status에 세팅을 하고 해당 스킬이 끝나면 다시 돌려줍니다.

	//Skill 사용중이 아니라면
	if (!UsingSkill)
	{
		int32 SkillNum = SkillTableRow.SkillDataArray.Num();

		//Skill 이 없다면 broadcast 시키고 return 하도록 한다
		if (SkillNum <= 0)
		{
			//
			//OnUsingSkill.Broadcast(UsingSkill, CanUseSkill, true);
			return;
		}




	}

	if (SkillTableRow.SkillDataArray.IsEmpty()) { return; }

	FSkillDataRow SkillData = SkillTableRow.SkillDataArray[IndexSkill];





}

//void USkillComponent::UseRangedSkill()
//{
//	bool Canuseskill = true;
//
//}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BasePlayer.h"
#include "Monster/PartyMonster.h"
#include "Monster/BaseMonster.h"
#include "StatusComponent.h"


// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatusComponent::AddEXP(float fGetEXP)
{
	//플레이어가 경험치를 받을 경우 파티 몬스터에게도 모두 경험치가 들어가도록 여기서 만들어야 합니다!!!!
	//TODO:: item 및 PartyMonster Status 의 EXP 획득 기능을 추가로 해야 합니다

	EXP += fGetEXP;
	OnEXPChanged.Broadcast(EXP, MaxEXP);
}

void UStatusComponent::AddHP(float Damage)
{
	{ 
		HP += Damage; 
		OnHPChanged.Broadcast(HP, MaxHP);
	}
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
	MaxEXP = (Level * 20) + (Level * (5 * Level));
	OnHPChanged.Broadcast(HP, MaxHP);
	OnMPChanged.Broadcast(MP, MaxMP);
	OnEXPChanged.Broadcast(EXP, MaxEXP);
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

float UStatusComponent::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDie) { return 0.f; }
	if (FMath::IsNearlyZero(Damage)) { return 0.0; }
	float NewDamage = Damage;

	// Ex. NewDamage -= Armor;
	NewDamage = FMath::Clamp(NewDamage, 0.f, NewDamage);

	HP -= NewDamage;
	HP = FMath::Clamp(HP, 0.f, HP);
	
	float MaxStun = MaxHP * 0.33f;
	
	LastInstigator = EventInstigator;
	OnHPChanged.Broadcast(HP, MaxHP);

	if (HP == 0.f)
	{
		bDie = true;
		//LastInstigator->GetPawn();
		APawn* LastInstigatorPawn = LastInstigator->GetPawn();

		//APawn* OwningPawn = Cast<APawn>(MeshComp->GetOwner());
		ABasePlayer* OwningPlayer = Cast<ABasePlayer>(LastInstigatorPawn);

		//cast 불가능한 PartyMonster나 Monster의 경우
		if (!OwningPlayer)
		{
			APartyMonster* PartyMonster = Cast<APartyMonster>(LastInstigatorPawn);
			if (PartyMonster) { LastInstigatorPawn = PartyMonster->GetOwnerPlayer(); }
			//Monster가 플레이어나 파티 몬스터를 죽인것임으로 경험치 줄 이유가 없음
			//else { return NewDamage; }
		}



		//위에서 LastInstigatorPawn을 player로 확정하게 바꿨으니 이후 플레이어는 얻은 경험치를 보유한 파티 몬스터에게 주도록 해야함 
		UStatusComponent* EventInstigatorStatusComponent = LastInstigatorPawn->GetComponentByClass<UStatusComponent>();
		check(EventInstigatorStatusComponent);
		//Monster가 플레이어나 파티 몬스터를 죽인것임으로 경험치 줄 이유가 없음
		// if Monster Die give Exp  Target Type 이 monster 가 아닐 경우 exp 주도록 설계
		if (OwnerPawnType != 1) 
		{ 
			//check
			int a = OwnerPawnType;
			EventInstigatorStatusComponent->AddEXP(EXP); 
		}

		OnDie.Broadcast();
	}

	return NewDamage;
}

void UStatusComponent::LevelUp()
{
	if (EXP >= MaxEXP)
	{
		++Level;
		EXP -= MaxEXP;
		MaxEXP = (Level * 20) + (Level * (5 * Level));

		//levelup status 추가 하는 과정 추가하고 밑에 broadcast 사용
		MaxHP += (EvolutionType * 10)+10;
		HP = MaxHP;
		STR += EvolutionType * 3 * Type;
		INT += EvolutionType * 3 * (4 - Type);
		STRDEF += EvolutionType * 3 * Type;
		INTDEF += EvolutionType * 3 * (4 - Type);

		OnHPChanged.Broadcast(HP, MaxHP);
		OnLevelChanged.Broadcast(Level);
		OnStatusChanged.Broadcast(STR, INT, STRDEF, INTDEF);

	}
	else { return; }



	return ;
}

bool UStatusComponent::KillEnemy()
{
	

	return false;
}


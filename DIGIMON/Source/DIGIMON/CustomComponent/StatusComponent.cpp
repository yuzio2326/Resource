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

		UStatusComponent* EventInstigatorStatusComponent = LastInstigatorPawn->GetComponentByClass<UStatusComponent>();
		check(EventInstigatorStatusComponent);
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


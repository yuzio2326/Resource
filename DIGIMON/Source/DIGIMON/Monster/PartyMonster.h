// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Data/PawnData.h"
#include "Misc/Utils.h"
#include "CustomComponent/AdvanceFloatingPawnMovement.h"
#include "Character/BasePlayer.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PartyMonster.generated.h"

USTRUCT()
struct DIGIMON_API FPartyMonsterTableRow : public FBasePawnData
{
	GENERATED_BODY()
	FPartyMonsterTableRow();
public:
	UPROPERTY(EditAnywhere, Category = "PartyMonster")
	TSubclassOf<APartyMonster> PartyMonsterClass;
	

};





DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOwningPlayer, bool, IsOwnPlayer, ABasePlayer*, PlayerTarget);

UCLASS()
class DIGIMON_API APartyMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APartyMonster();
	virtual void SetData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetSkillData(const FDataTableRowHandle& InSkillDataTableRowHandle);
protected:
	//Duplacte In Editor
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	USkillComponent* GetMonsterSkilRow() const { return SkillComponent; }
	UStatusComponent* GetMonsterStatus() const { return StatusComponent; }
	// Called to bind functionality to input
	
	//안쓸지도?
	//bool OwningPlayer() { return IsOwnPlayer = SkillComponent->GetOwnerPlayer(); }
	ABasePlayer* GetOwnerPlayer() { return OwnPlayer; }

	void SetOwnerPlayer(ABasePlayer* InOwnPlayerTarget);

protected:
	UFUNCTION()
	virtual void OnDie();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY()
	TObjectPtr<UShapeComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/Digimon.BasePawnData"))
	FDataTableRowHandle BaseDataTableRowHandle;

	FBasePawnData* PawnData;

	UPROPERTY(VisibleAnywhere)
	UAdvanceFloatingPawnMovement* MovementComponent;
	UPROPERTY(VisibleAnywhere)
	UStatusComponent* StatusComponent;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere)
	UAISenseConfig_Sight* AISenseConfig_Sight;
	UPROPERTY(VisibleAnywhere)
	UAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	USkillComponent* SkillComponent;

	FSkillTableRow* MonsterSkillData;

	UAnimMontage* CurrentDieMontage;

	UPROPERTY(BlueprintAssignable)
	FOwningPlayer IsOwnPlayer;


	ABasePlayer* OwnPlayer;

};

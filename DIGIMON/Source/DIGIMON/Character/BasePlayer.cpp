// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/BasePlayer.h"
#include "CustomComponent/NoFallCharacterMovementComponent.h"
#include "Character/BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSprite.h"


// Sets default values
ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNoFallCharacterMovementComponent>(Super::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Weapon = CreateDefaultSubobject<UWeaponChildActorComponent>(TEXT("Weapon"));
	//TODO::
	//spawn static 총 mesh spawn 시키고 muzzle 위치 설정하기
	//레벨업 관련 ui 만들기 skillcomponent에서 원거리 공격 하는걸로 하도록 설정해가지고 자기 stat 추가뎀 만들기     	

	{
		SpringArm->SetupAttachment(GetMesh());
		SpringArm->ProbeSize = 5.0;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->SetMinMaxTargetArmLength(200.f, SpringArm->GetMaxTargetArmLength());
	}
	Camera->SetupAttachment(SpringArm);
	Weapon->SetupAttachment(GetMesh(), SocketName::Weapon);

	bUseControllerRotationYaw = false;

	//UCharacterMovementComponent* Movement = GetCharacterMovement();
	//Movement->bCanWalkOffLedges = false;
	const FRotator Rotation = FRotator(0., 90.0, 0.);
	const FVector Translation = FVector(0., 0., 90.0);
	FTransform SpringArmTransform = FTransform(Rotation, Translation, FVector::OneVector);
	SpringArm->SetRelativeTransform(SpringArmTransform);

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	

	// Minimap		minimap 대신 그냥 worldmap 하나만 할까 고민중...  
	{
		MinimapSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapSpriteComponent"));
		MinimapSpriteComponent->SetupAttachment(RootComponent);
		MinimapSpriteComponent->SetVisibleInSceneCaptureOnly(true);
		{
			FTransform Transform;
			Transform.SetLocation(FVector(0.0, 0.0, 300.0));
			Transform.SetRotation(FRotator(0.0, 90.0, -90.0).Quaternion());
			MinimapSpriteComponent->SetRelativeTransform(Transform);
		}
		{
			//static ConstructorHelpers::FObjectFinder<UPaperSprite> Asset(TEXT("/Script/Paper2D.PaperSprite'/Game/Digimon/UI/Icon/Icon_Player_Sprite.Icon_Player_Sprite'"));
			//ensure(Asset.Object);
			//MinimapSpriteComponent->SetSprite(Asset.Object);
		}
		//{
		//	static ConstructorHelpers::FObjectFinder<UMaterial> Asset(TEXT("/Script/Engine.Material'/Game/Digimon/UI/MyDefaultSpriteMaterial.MyDefaultSpriteMaterial'"));
		//	ensure(Asset.Object);
		//	MinimapSpriteComponent->SetMaterial(0, Asset.Object);
		//}
	}
}



void ABasePlayer::OnDie()
{
	AnimInstance->Montage_Pause(CurrentDieMontage);
}

void ABasePlayer::Attack()
{
	//몽타주 플레이중이 아니면
	ABasePlayerController* OwnPlayerController = Cast<ABasePlayerController>(GetController());
	check(OwnPlayerController);

	if (!AnimInstance->Montage_IsPlaying(nullptr)&& OwnPlayerController->IsZoom)
	{
		//어차피 하나만 쓸거임 괜히 array로 만들었네..
		AnimInstance->Montage_Play(CharacterData->AttackMontage[0]);
		//PlayAnimMontage(CharacterData->AttackMontage[0], 1.0f, FName("UpperBody"));
	}
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<AActor> MinimapClass = LoadClass<AActor>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Digimon/UI/Minimap/BP_Minimap.BP_Minimap'"));
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner = this;
	AActor* MinimapActor = GetWorld()->SpawnActor<AActor>(MinimapClass, ActorSpawnParameters);
}

void ABasePlayer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetData(DataTableRowHandle);
}

bool ABasePlayer::CanJumpInternal_Implementation() const
{
	return false;
}

void ABasePlayer::SetData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	FBasePawnData* Data = DataTableRowHandle.GetRow<FBasePawnData>(TEXT("Character"));
	if (!Data) { ensure(false); return; }

	CharacterData = Data;
	{
		UCharacterMovementComponent* Movement = GetCharacterMovement();
		//Movement->RotationRate = CharacterData->RotationRate;
		Movement->bOrientRotationToMovement = true;
		Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
		Movement->MaxWalkSpeed = CharacterData->MovementMaxSpeed;

		const float NewCapsuleHalfHeight = CharacterData->CollisionCapsuleHalfHeight * 0.5f;
		Movement->SetCrouchedHalfHeight(NewCapsuleHalfHeight);
	}
	{
		UCapsuleComponent* Capsule = GetCapsuleComponent();
		if (!FMath::IsNearlyEqual(Capsule->GetUnscaledCapsuleHalfHeight(), CharacterData->CollisionCapsuleHalfHeight))
		{
			Capsule->SetCapsuleHalfHeight(CharacterData->CollisionCapsuleHalfHeight, false);
		}
	}
	{
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		SkeletalMeshComponent->SetSkeletalMesh(CharacterData->SkeletalMesh);
		SkeletalMeshComponent->SetRelativeTransform(CharacterData->MeshTransform);
		SkeletalMeshComponent->SetAnimClass(CharacterData->AnimClass);

		AnimInstance = Cast<UPawnAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
		check(AnimInstance);
	}
	{
		if (CharacterData->Level != 0 && CharacterData->HP != 0 && CharacterData->PawnType != 0 && StatusComponent)
		{
			StatusComponent->StatusSetting(CharacterData->Level, CharacterData->EXP, CharacterData->HP, CharacterData->MP, CharacterData->STR, CharacterData->STR_DEF, CharacterData->INT, CharacterData->INT_DEF, CharacterData->PawnType);
		}
	}
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Hpcheck = StatusComponent->GetHP();
	if (Hpcheck > 0)
	{
		int a = 0;
	}

	if (StatusComponent->GetAttack())
	{
		Attack();
	}

}

void ABasePlayer::UpdateDesiredAimRotation(const float DeltaTime)
{
	{
		APawn* OwningPawn = Cast<APawn>(GetOwner());
		const FRotator OwnerRotation = GetOwner()->GetActorRotation();
		FRotator OwnerInvRotation = OwnerRotation.GetInverse();
		OwnerInvRotation.Roll = 0.;
		FRotator ControlRotation = OwningPawn->GetControlRotation();
		ControlRotation.Roll = 0.;
		FRotator NewRotation = UKismetMathLibrary::ComposeRotators(OwnerInvRotation, ControlRotation);

		DesiredAimRotation.Pitch = NewRotation.Pitch;
		DesiredAimRotation.Yaw = UKismetMathLibrary::ClampAngle(NewRotation.Yaw, -100.0, 100.0);
		DesiredAimRotation.Roll = NewRotation.Roll;
	}
	{
		const float NewDeltaTime = FMath::Clamp(DeltaTime, 0.f, 0.03f);
		const FRotator& AimRotation = AnimInstance->GetAimRotation();
		const float Alpha = NewDeltaTime * 10.f;
		const FRotator LerpShortestPathRotation = UKismetMathLibrary::RLerp(AimRotation, DesiredAimRotation, Alpha, true);
		const FRotator LerpRotation = UKismetMathLibrary::RLerp(AimRotation, DesiredAimRotation, Alpha, false);
		FRotator NewRotation = FRotator(LerpShortestPathRotation.Pitch, LerpRotation.Yaw, LerpShortestPathRotation.Roll);
		AnimInstance->SetAimRotation(NewRotation);
	}
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (StatusComponent->IsDie()) { return 0.0f; }

	
	if (StatusComponent->GetHP() > 0)
	{

		//StatusComponent->AddHP(Damage);
		StatusComponent->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}


	return 0.0f;
}


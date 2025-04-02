// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomComponent/NoFallCharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaperSprite.h"
#include "Character/BasePlayer.h"

// Sets default values
ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UNoFallCharacterMovementComponent>(Super::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(CollisionProfileName::Player);
	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	{
		SpringArm->SetupAttachment(GetMesh());
		SpringArm->ProbeSize = 5.0;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
		SpringArm->SetMinMaxTargetArmLength(400.f, SpringArm->GetMaxTargetArmLength());
	}
	Camera->SetupAttachment(SpringArm);
	

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
			static ConstructorHelpers::FObjectFinder<UPaperSprite> Asset(TEXT("/Script/Paper2D.PaperSprite'/Game/Digimon/UI/Icon/Icon_Player_Sprite.Icon_Player_Sprite'"));
			ensure(Asset.Object);
			MinimapSpriteComponent->SetSprite(Asset.Object);
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
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Pause(CurrentDieMontage);
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
	}
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABasePlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}


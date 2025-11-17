// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/Minions/VMEnemySpawnSiege.h"

#include "Core/VMMonsterEnums.h"
#include "AI/Enemies/VMEnemySpawnBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile/VMStraightProjectile.h"


AVMEnemySpawnSiege::AVMEnemySpawnSiege()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Project/Animation/ABP_SpawnEnemySiege.ABP_SpawnEnemySiege_C'"));
	ensureAlways(AnimInstanceRef.Class);
	if (AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}

	// Skeletal Mesh 입히기
#pragma region SkeletalMesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Siege_Dawn.Minion_Lane_Siege_Dawn'"));
	ensureAlways(MeshRef.Object);
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
#pragma endregion

#pragma region AnimationClass
	ConstructorHelpers::FClassFinder<AController> AIControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/ProjectVM.VMSpawnAIControllerBase'"));
	ensureAlways(AIControllerClassRef.Class);
	if (AIControllerClassRef.Class)
	{
		AIControllerClass = AIControllerClassRef.Class;
	}
#pragma endregion

	ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Project/Animation/VM_SiegeAttackDefault.VM_SiegeAttackDefault'"));
	if (NormalAttackMontageRef.Object)
	{
		NormalAttackMontage = NormalAttackMontageRef.Object;
	}

MoveSpeed = 100.0f;
AttackSpeed = 1.0f;
AttackRange = 2000.0f;
TurnSpeed = 2.0f;
}

void AVMEnemySpawnSiege::BeginPlay()
{
	Super::BeginPlay();
	SetMonsterType(EMonsterName::MinionSiege);
}

void AVMEnemySpawnSiege::NormalAttack()
{
	UE_LOG(LogTemp, Log, TEXT("AVMEnemySpawnSiege::NormalAttack"));
	Super::NormalAttack();

	FVector Location = GetActorLocation();
	FVector SpawnLocation = Location + GetActorForwardVector() * 100.0f;
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	PlayNormalAttackMontage();

	AVMStraightProjectile* Projectile = GetWorld()->SpawnActor<AVMStraightProjectile>(AVMStraightProjectile::StaticClass(), SpawnTransform);
	if (Projectile == nullptr)
	{
		return;
	}

	Projectile->SetMaxSpeed(2000.0f);
	Projectile->SetVelocity(2000.0f);

	UE_LOG(LogTemp, Display, TEXT("Siege가 발사한 Projectile을 생성하였습니다."));
}

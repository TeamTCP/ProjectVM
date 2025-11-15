// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/Minions/VMEnemySpawnSuper.h"

AVMEnemySpawnSuper::AVMEnemySpawnSuper()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Project/Animation/ABP_SpawnEnemySuper.ABP_SpawnEnemySuper_C'"));
	ensureAlways(AnimInstanceRef.Class);
	if (AnimInstanceRef.Class)
	{
		GetMesh()->SetAnimClass(AnimInstanceRef.Class);
	}

	// Skeletal Mesh 입히기
#pragma region SkeletalMesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Super_Dusk.Minion_Lane_Super_Dusk'"));
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

	ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttackMontageRef(TEXT("Script/Engine.AnimMontage'/Game/Project/Animation/VM_SuperAttackDefault.VM_SuperAttackDefault'"));
	if (NormalAttackMontageRef.Object)
	{
		NormalAttackMontage = NormalAttackMontageRef.Object;
	}

	MoveSpeed = 200.0f;
	AttackSpeed = 1.0f;
	AttackRange = 300.0f;
	TurnSpeed = 2.0f;
}

void AVMEnemySpawnSuper::BeginPlay()
{
	Super::BeginPlay();

	SetMonsterType(EMonsterName::MinionSuper);
}

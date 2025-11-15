// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTTask_SpawnNormalAttack.h"

#include "AIController.h"
#include "AI/Enemies/VMEnemySpawnBase.h"

UBTTask_SpawnNormalAttack::UBTTask_SpawnNormalAttack()
{
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_SpawnNormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIControllerPtr = OwnerComp.GetAIOwner();
	if (AIControllerPtr == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* PawnPtr = AIControllerPtr->GetPawn();
	if (PawnPtr == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AVMEnemySpawnBase* EnemyPtr = Cast<AVMEnemySpawnBase>(PawnPtr);
	if (EnemyPtr == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	EnemyPtr->NormalAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_SpawnNormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	AVMEnemySpawnBase* Character = Cast<AVMEnemySpawnBase>(AIController->GetPawn());
	if (!Character)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (AnimInstance->Montage_IsPlaying(Character->GetNormalMontage()) == true)
	{
		return;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
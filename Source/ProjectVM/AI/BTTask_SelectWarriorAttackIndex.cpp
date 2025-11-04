// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SelectWarriorAttackIndex.h"

#include "AIController.h"
#include "VMEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

#pragma region 특수_맴버_함수

UBTTask_SelectWarriorAttackIndex::UBTTask_SelectWarriorAttackIndex()
{
	NodeName = TEXT("SelectRandomIndex");
}

#pragma endregion

#pragma region 엔진_제공_함수

EBTNodeResult::Type UBTTask_SelectWarriorAttackIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AVMEnemyBase* EnemyPtr = Cast<AVMEnemyBase>(PawnPtr);
	if (EnemyPtr == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// TODO: 하드 코딩 값 변경 필요.
	int32 Index = FMath::RandRange(0, 2);

	UBlackboardComponent* BBComponentPtr = AIControllerPtr->GetBlackboardComponent();
	if (BBComponentPtr == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	// 정해진 값을 Index에 저장.
	BBComponentPtr->SetValueAsInt(TEXT("AttackRandomIndex"), Index);

	return EBTNodeResult::Succeeded;
}

#pragma endregion

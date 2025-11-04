// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolPos.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Macro/VMAIMarco.h"

#pragma region 특수_맴버_함수

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
    NodeName = TEXT("FindPatrolPos");
}

#pragma endregion

#pragma region 엔진_제공_함수

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 부모 함수 호출
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    // BehaviourTreeComponent를 소유하는 컨트롤러가 제어하는 폰 정보 가져오기.
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

    // 내비게이션 시스템을 활용하기 위한 포인터 가져오기.
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(PawnPtr->GetWorld());

    // 네비게이션의 유효성 검사.
    if (NavSystem == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* BBComponentPtr = OwnerComp.GetBlackboardComponent();
    ensure(BBComponentPtr == AIControllerPtr->GetBlackboardComponent());

    // 폰이 생성된 초기 위치 가져오기.
    FVector InitialPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);

    // 내비게이션 시스템을 활용해 랜덤으로 위치 선택. TODO: 하드코딩 지우기
    FNavLocation NextPatrolPos;
    if (NavSystem->GetRandomPointInNavigableRadius(InitialPos, 500.0f, NextPatrolPos))
    {
        // 랜덤 위치가 선택되면, 블랙보드에 선택된 위치 저장.
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}

#pragma endregion

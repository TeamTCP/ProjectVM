// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_WarriorMoveBehindTarget.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_WarriorMoveBehindTarget::UBTTask_WarriorMoveBehindTarget()
{
    NodeName = TEXT("Teleport Behind Target");
}

EBTNodeResult::Type UBTTask_WarriorMoveBehindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    ACharacter* OwnerChar = Cast<ACharacter>(AICon->GetPawn());
    if (!OwnerChar) return EBTNodeResult::Failed;

    AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
    if (!Target) return EBTNodeResult::Failed;

    // 타겟의 뒤쪽 방향 계산
    FVector BackDir = -Target->GetActorForwardVector();
    FVector TeleportLocation = Target->GetActorLocation() + BackDir * 200.f; // 200cm 뒤로
    TeleportLocation.Z = OwnerChar->GetActorLocation().Z;

    OwnerChar->SetActorLocation(TeleportLocation, false, nullptr, ETeleportType::TeleportPhysics);

    return EBTNodeResult::Succeeded;
}
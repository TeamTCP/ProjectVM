// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask/BTTask_TurnToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Interface/VMAIEnemyBaseInterface.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	// 노드 이름 설정.
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result= Super::ExecuteTask(OwnerComp, NodeMemory);

	// NPC가 캐릭터를 바라보는 방향.
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("너니1"));
		return EBTNodeResult::Failed;
	}

	// 캐릭터 구하기.
	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("EnemyTarget")));

	if (TargetPawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("너니2"));
		return EBTNodeResult::Failed;
	}

	// AIPawn 구하기.
	IVMAIEnemyBaseInterface* AIPawn = Cast<IVMAIEnemyBaseInterface>(ControllingPawn);
	if (AIPawn == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("너니3"));
		return EBTNodeResult::Failed;
	}

	// NPC가 바라볼 방향 구하기.
	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();

	// 회전 값 구하기.
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	// DeltaTime.
	UWorld* World = ControllingPawn->GetWorld();



	// 회전 속도.
	float TurnSpeed = 3;

	// 부드럽게 회전 처리.
	FRotator FinalRotator = FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, World->GetDeltaSeconds(), TurnSpeed);

	// 회전 설정.
	ControllingPawn->SetActorRotation(FinalRotator);

	return EBTNodeResult::Succeeded;
}
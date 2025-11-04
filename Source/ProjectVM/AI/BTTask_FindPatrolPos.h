// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

#pragma region 특수_맴버_함수
public:
	UBTTask_FindPatrolPos();
#pragma endregion

#pragma region 엔진_제공_함수
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
#pragma endregion
};

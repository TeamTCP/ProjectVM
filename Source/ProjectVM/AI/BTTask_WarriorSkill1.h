// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WarriorSkill1.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTTask_WarriorSkill1 : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_WarriorSkill1();
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool bIsAttacking = false;
	float ElapsedTime = 0.0f;
};

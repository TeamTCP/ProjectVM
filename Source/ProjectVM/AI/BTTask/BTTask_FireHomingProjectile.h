// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FireHomingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTTask_FireHomingProjectile : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FireHomingProjectile();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	EBTNodeResult::Type SpawnAroundAll(UBehaviorTreeComponent& OwnerComp, class AVMEnemyBoss*);
	EBTNodeResult::Type SpawnForwardRand(UBehaviorTreeComponent& OwnerComp, class AVMEnemyBoss*);
};

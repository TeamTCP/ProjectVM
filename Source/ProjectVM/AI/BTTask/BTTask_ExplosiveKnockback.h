// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ExplosiveKnockback.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTTask_ExplosiveKnockback : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ExplosiveKnockback();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

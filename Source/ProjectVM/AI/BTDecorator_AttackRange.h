// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTDecorator_AttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
#pragma region 특수_맴버_함수
public:
	UBTDecorator_AttackRange();
#pragma endregion

#pragma region 엔진_제공_함수
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
#pragma endregion
};

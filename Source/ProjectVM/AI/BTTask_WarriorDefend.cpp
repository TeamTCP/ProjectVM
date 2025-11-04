// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_WarriorDefend.h"

#pragma region 특수_맴버_함수

UBTTask_WarriorDefend::UBTTask_WarriorDefend()
{
	NodeName = TEXT("WarriorDefend");
}

#pragma endregion

#pragma region 엔진_제공_함수

EBTNodeResult::Type UBTTask_WarriorDefend::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

#pragma endregion

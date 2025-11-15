// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/VMEnemySpawnBase.h"
#include "VMEnemySpawnSuper.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API AVMEnemySpawnSuper : public AVMEnemySpawnBase
{
	GENERATED_BODY()

public:
	AVMEnemySpawnSuper();
public:
	virtual void BeginPlay() override;
public:
	virtual float GetAIMoveSpeed() const { return MoveSpeed; }
	virtual float GetAIAttackRange() const { return AttackRange; }
	virtual float GetAITurnSpeed() const { return TurnSpeed; }
};

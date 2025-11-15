// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/VMEnemySpawnBase.h"
#include "VMEnemySpawnSiege.generated.h"

/**
 *
 */
UCLASS()
class PROJECTVM_API AVMEnemySpawnSiege : public AVMEnemySpawnBase
{
	GENERATED_BODY()

public:
	AVMEnemySpawnSiege();

public:
	virtual void BeginPlay() override;
public:
	virtual float GetAIMoveSpeed() const { return MoveSpeed; }
	virtual float GetAIAttackRange() const { return AttackRange; }
	virtual float GetAITurnSpeed() const { return TurnSpeed; }

	virtual void NormalAttack() override;
};

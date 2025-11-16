// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FireStraightProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UBTTask_FireStraightProjectile : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FireStraightProjectile();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	// case 1: 내 방향으로 1발 쏘기
	EBTNodeResult::Type SpawnProjectileToTarget(UBehaviorTreeComponent& OwnerComp, class AVMEnemyBoss*);

	// case 2: 내 방향을 보면서 각도별로 1발씩 쏘기(총 10번?)
	EBTNodeResult::Type SpawnProjectilesStraight(UBehaviorTreeComponent& OwnerComp, class AVMEnemyBoss*);

	// case 3: 4000m에서 내 방향으로 날라오기
	EBTNodeResult::Type SpawnFromFront(UBehaviorTreeComponent& OwnerComp, AVMEnemyBoss* BossPtr);

	// case 4: 내 방향에서 각도를 찾고 12발 돌리기
	EBTNodeResult::Type SpawnCircleStraight(UBehaviorTreeComponent& OwnerComp, AVMEnemyBoss* BossPtr);

	// case 5: 내 중심에서 하늘에서 10발 떨구기
	EBTNodeResult::Type SpawnGangplankUlt(UBehaviorTreeComponent& OwnerComp, AVMEnemyBoss* BossPtr);

	static class AVMStraightProjectile* SpawnStraightProjectile(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation, const FActorSpawnParameters& Params);


private:
	int32 ShotsFired = 0;

	FTimerHandle VerticalShotTimer;
	const int32 TotalShots = 12;
	void FireOneVerticalProjectile(UBehaviorTreeComponent* OwnerComp, AVMEnemyBoss* BossPtr);

	const int32 CircleTotalShots = 36;
	FTimerHandle CircleShotTimer;

	void FireOneCircleProjectile(UBehaviorTreeComponent* OwnerComp, AVMEnemyBoss* BossPtr);

	int32 SpawnTotalCount = 20;
	int32 SpawnFinishedCount = 0;
};

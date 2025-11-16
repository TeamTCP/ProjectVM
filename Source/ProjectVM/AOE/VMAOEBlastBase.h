// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AOE/VMAOEBase.h"
#include "VMAOEBlastBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API AVMAOEBlastBase : public AVMAOEBase
{
	GENERATED_BODY()

public:
	AVMAOEBlastBase();

public:
	virtual void SpawnAOESphere() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Member, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystem> BlastEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Member, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundBase> BlastSound;

	UFUNCTION()
	void OnFinishParticle(UParticleSystemComponent* ParticleSystem);

	void SpawnBlastEffect();

	void PlayBlastSound();
	
};

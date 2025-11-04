// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/VMItemInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTVM_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void StatBoost(class VMHeroStatComponent* StatComponent);
	virtual void EquipEffect(class AVMCharacterHeroBase* Owner);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	FVMItemInfo ItemInfo;
};

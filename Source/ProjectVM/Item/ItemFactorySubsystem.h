// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/VMItemInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemFactorySubsystem.generated.h"

/**
 * 
 */

class UItemBase;

UCLASS()
class PROJECTVM_API UItemFactorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UItemBase* CreateRandomMaterialItem();
	UItemBase* CreateItemByID(int32 Level);
	UItemBase* CreateItemByName(FString Name);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	TArray<TSubclassOf<class UItemBase>> AllItemClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TMap<FName, TSubclassOf<class UItemBase>> ItemClassByName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TMap<int32, TSubclassOf<class UItemBase>> ItemClassByID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TMap<FName, FVMItemInfo> ItemInfoByName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemData")
	TMap<int32, FVMItemInfo> ItemInfoByID;
};

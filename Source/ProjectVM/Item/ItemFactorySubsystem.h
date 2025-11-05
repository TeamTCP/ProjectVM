// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equipment/VMEquipmentInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemFactorySubsystem.generated.h"

/**
 * 
 */

class UVMEquipoment;

UCLASS()
class PROJECTVM_API UItemFactorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UVMEquipoment* CreateRandomBaseEquipment();
	UVMEquipoment* CreateItemByName(FString Name);
	UVMEquipoment* CraftEquipment();

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<FVMEquipmentInfo> AllEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<FVMEquipmentInfo> BaseEquipment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<FName, FVMEquipmentInfo> EquipmentInfoByName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<int32, FVMEquipmentInfo> EquipmentInfoByID;
};

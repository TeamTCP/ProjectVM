// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemFactorySubsystem.h"
#include "Item/Equipment/VMEquipment.h"

UVMEquipoment* UItemFactorySubsystem::CreateRandomBaseEquipment()
{
	return nullptr;
}

UVMEquipoment* UItemFactorySubsystem::CreateItemByName(FString Name)
{
	return nullptr;
}

UVMEquipoment* UItemFactorySubsystem::CraftEquipment()
{
	return nullptr;
}

void UItemFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UDataTable* EquipmentDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Project/Item/VMEquipmentInfo.VMEquipmentInfo"));
	if (EquipmentDataTable == nullptr) return;

	for (const FName& RowName : EquipmentDataTable->GetRowNames())
	{
		FVMEquipmentInfo* EquipmentInfoPtr = EquipmentDataTable->FindRow<FVMEquipmentInfo>(RowName, TEXT(""));
		if (EquipmentInfoPtr == nullptr) continue;

		AllEquipment.Add(*EquipmentInfoPtr);
		if (EquipmentInfoPtr->ItemLevel == 1) BaseEquipment.Add(*EquipmentInfoPtr);

		EquipmentInfoByName.Add(FName(EquipmentInfoPtr->ItemName), *EquipmentInfoPtr);
		EquipmentInfoByID.Add(EquipmentInfoPtr->ItemID, *EquipmentInfoPtr);
	}
}

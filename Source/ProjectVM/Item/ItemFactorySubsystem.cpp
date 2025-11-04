// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemFactorySubsystem.h"
#include "Item/ItemBase.h"

UItemBase* UItemFactorySubsystem::CreateRandomMaterialItem()
{
	return nullptr;
}

UItemBase* UItemFactorySubsystem::CreateItemByID(int32 Level)
{
	return nullptr;
}

UItemBase* UItemFactorySubsystem::CreateItemByName(FString Name)
{
	return nullptr;
}

void UItemFactorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	for (TSubclassOf<UItemBase> ItemClass : AllItemClasses)
	{
		FName ClassName = ItemClass->GetFName();
		
		ItemClassByName.Add(ClassName, ItemClass);
	}

	UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Project/Item/VMItemInfo.VMItemInfo"));
	if (ItemDataTable == nullptr) return;

	for (const FName& RowName : ItemDataTable->GetRowNames())
	{
		FVMItemInfo* ItemInfo = ItemDataTable->FindRow<FVMItemInfo>(RowName, TEXT(""));
		if (ItemInfo == nullptr) continue;

		TSubclassOf<UItemBase>* ItemClassPtr = ItemClassByName.Find(ItemInfo->ClassName);
		if (ItemClassPtr == nullptr || *ItemClassPtr == nullptr) continue;

		ItemClassByID.Add(ItemInfo->ItemID, *ItemClassPtr);
		ItemInfoByName.Add(ItemInfo->ClassName, *ItemInfo);
		ItemInfoByID.Add(ItemInfo->ItemID, *ItemInfo);
	}
}

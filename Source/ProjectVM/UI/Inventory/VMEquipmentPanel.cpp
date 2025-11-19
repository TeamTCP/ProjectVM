// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/VMEquipmentPanel.h"


#include "UI/Inventory/VMInventoryItemSlot.h"
#include "Hero/VMCharacterHeroBase.h"
#include "Item/Equipment/VMEquipment.h"
#include "Item/Equipment/VMEquipmentInfo.h"


void UVMEquipmentPanel::NativeConstruct()
{
    Super::NativeConstruct();

    SlotWidgets.Empty();
    SlotWidgets.Add(Weapon_Slot0);
    SlotWidgets.Add(Weapon_Slot1);
    SlotWidgets.Add(Weapon_Slot2);
    SlotWidgets.Add(Weapon_Slot3);
    SlotWidgets.Add(Weapon_Slot4);
    SlotWidgets.Add(Weapon_Slot5);

    UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel::NativeConstruct - SlotWidgets.Num = %d"), SlotWidgets.Num());

    int32 Index = 0;
    for (UVMInventoryItemSlot* Weapon_Slot : SlotWidgets)
    {
        if (Weapon_Slot)
        {
            UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: Slot %d is valid"), Index);
            Weapon_Slot->SetItemReference(nullptr);  // 처음엔 빈칸
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: Slot %d is NULL"), Index);
        }
        ++Index;
    }
}

int32 UVMEquipmentPanel::TryEquipToEmptySlot(UVMEquipment* Item)
{

    if (!Item)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel::TryEquipToEmptySlot - Item is NULL"));
        return INDEX_NONE;
    }

    UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel::TryEquipToEmptySlot called for %s"),
        *Item->GetEquipmentInfo().ItemName);

    if (SlotWidgets.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel::TryEquipToEmptySlot - SlotWidgets empty"));
        return INDEX_NONE;
    }

    // 첫 번째 빈칸 찾기
    for (int32 i = 0; i < SlotWidgets.Num(); ++i)
    {
        UVMInventoryItemSlot* Weapon_Slot = SlotWidgets[i];
        if (!Weapon_Slot)
        {
            UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: Slot %d is NULL"), i);
            continue;
        }

        if (Weapon_Slot->GetItemReference() == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: Equip to slot %d"), i);
            Weapon_Slot->SetItemReference(Item);
            return i;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: No empty slot found (all slots have item)"));
    return INDEX_NONE;
}

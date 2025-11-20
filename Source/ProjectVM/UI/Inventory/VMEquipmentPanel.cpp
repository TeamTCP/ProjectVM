// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/VMEquipmentPanel.h"
#include "UI/Inventory/VMEquipmentItemSlot.h"
#include "UI/Inventory/VMInventoryItemSlot.h"
#include "Inventory/VMInventoryComponent.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Item/Equipment/VMEquipment.h"

#include "Components/Widget.h"


void UVMEquipmentPanel::NativeConstruct()
{

    Super::NativeConstruct();

    WeaponSlots.Empty();
    WeaponSlots.Add(Weapon_Slot0);
    WeaponSlots.Add(Weapon_Slot1);
    WeaponSlots.Add(Weapon_Slot2);
    WeaponSlots.Add(Weapon_Slot3);
    WeaponSlots.Add(Weapon_Slot4);
    WeaponSlots.Add(Weapon_Slot5);

    // 시작은 전부 빈칸
    for (UVMInventoryItemSlot* EquipSlot : WeaponSlots)
    {
        if (EquipSlot)
        {
            EquipSlot->ClearItem();
        }
    }
}

int32 UVMEquipmentPanel::TryEquipToEmptySlot(UVMEquipment* Item)
{
    if (!Item) return INDEX_NONE;

    for (int32 i = 0; i < WeaponSlots.Num(); ++i)
    {
        UVMInventoryItemSlot* EquipSlot = WeaponSlots[i];
        if (!EquipSlot)
            continue;

        if (EquipSlot->GetItemReference() == nullptr)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("EquipmentPanel: Equip to slot %d (SlotWidget=%s)"),
                i, *EquipSlot->GetName());

            EquipSlot->SetItemReference(Item);   // ★ 이거 하나만 해야 함

            return i;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("EquipmentPanel: No free equipment slot"));
    return INDEX_NONE;

}

void UVMEquipmentPanel::ClearItem()
{
    for (UVMInventoryItemSlot* EquipSlot : WeaponSlots)
    {
        if (EquipSlot)
        {
            EquipSlot->ClearItem();  // 이제는 브러시 안 지우니까 이대로 사용 가능
        }
    }
}

void UVMEquipmentPanel::RefreshFromItem()
{

}
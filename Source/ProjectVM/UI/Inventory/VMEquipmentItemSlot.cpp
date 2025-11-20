// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/VMEquipmentItemSlot.h"

#include "Item/Equipment/VMEquipmentInfo.h"
#include "Item/Equipment/VMEquipment.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"


void UVMEquipmentItemSlot::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Warning,
        TEXT("EquipmentItemSlot::NativeConstruct %s, AtlasMaterial=%s"),
        *GetName(),
        *GetNameSafe(AtlasMaterial));

    if (ItemBorder)
    {
        ItemBorder->SetBrushColor(FLinearColor::Transparent);
    }

    // Atlas 머터리얼에서 MID 생성
    if (ItemIcon && AtlasMaterial)
    {
        ItemMaterialInstance = UMaterialInstanceDynamic::Create(AtlasMaterial, this);
        ItemIcon->SetBrushFromMaterial(ItemMaterialInstance);
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("EquipmentItemSlot::NativeConstruct AtlasMaterial or ItemIcon is NULL"));
    }

    // 시작은 숨김
    if (ItemIcon)  ItemIcon->SetVisibility(ESlateVisibility::Hidden);
    if (ItemBorder) ItemBorder->SetVisibility(ESlateVisibility::Hidden);

}

void UVMEquipmentItemSlot::SetItem(UVMEquipment* InItem)
{

    UE_LOG(LogTemp, Warning, TEXT("EquipSlot::SetItem called, Item: %s"),
        InItem ? *InItem->GetEquipmentInfo().ItemName : TEXT("NULL"));

    ItemReference = InItem;
    RefreshFromItem();
}

void UVMEquipmentItemSlot::ClearItem()
{
    ItemReference = nullptr;
    RefreshFromItem();
}

void UVMEquipmentItemSlot::RefreshFromItem()
{
    UE_LOG(LogTemp, Warning,
        TEXT("EquipmentItemSlot::RefreshFromItem ENTER, AtlasMaterial=%s, MID=%s"),
        *GetNameSafe(AtlasMaterial),
        *GetNameSafe(ItemMaterialInstance));

    if (!ItemIcon || !ItemBorder)
        return;

    // 아이템 없으면 숨기기
    if (!ItemReference)
    {
        ItemIcon->SetVisibility(ESlateVisibility::Hidden);
        ItemBorder->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    const FVMEquipmentInfo& Info = ItemReference->GetEquipmentInfo();

    // 혹시라도 MID 날아갔으면 다시 생성
    if (!ItemMaterialInstance && AtlasMaterial)
    {
        ItemMaterialInstance = UMaterialInstanceDynamic::Create(AtlasMaterial, this);
        ItemIcon->SetBrushFromMaterial(ItemMaterialInstance);
    }

    if (ItemMaterialInstance)
    {
        UE_LOG(LogTemp, Warning,
            TEXT("EquipmentItemSlot::Set Params Col=%d Row=%d"),
            Info.AtlasCol, Info.AtlasRow);

        ItemMaterialInstance->SetScalarParameterValue(TEXT("ColumnIndex"), Info.AtlasCol);
        ItemMaterialInstance->SetScalarParameterValue(TEXT("RowIndex"), Info.AtlasRow);
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("EquipmentItemSlot::RefreshFromItem ItemMaterialInstance is STILL NULL"));
    }

    ItemIcon->SetVisibility(ESlateVisibility::Visible);
    ItemBorder->SetVisibility(ESlateVisibility::Visible);
}

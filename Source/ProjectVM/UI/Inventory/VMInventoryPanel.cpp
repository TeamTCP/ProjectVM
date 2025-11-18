// Fill out your copyright notice in the Description page of Project Settings.



#include "UI/Inventory/VMInventoryPanel.h"
#include "UI/Inventory/VMInventoryItemSlot.h"
#include "UI/Inventory/VMEquipmentPanel.h"
#include "Inventory/VMInventoryComponent.h"
#include "Hero/VMCharacterHeroBase.h"
#include "UI/Character/VMCharacterHeroHUD.h"


#include "Components/WrapBox.h"
#include "Components/TextBlock.h"



void UVMInventoryPanel::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    Character = Cast<AVMCharacterHeroBase>(GetOwningPlayerPawn());

    if (Character)
    {
        InventoryReference = Character->GetInventory();
        if (InventoryReference)
        {
            InventoryReference->OnInventoryUpdated.AddUObject(this, &UVMInventoryPanel::RefreshInventory);
            SetInfoText();
        }
    }
}

void UVMInventoryPanel::RefreshInventory()
{

    const TArray<UVMEquipment*>& Contents = InventoryReference->GetInventoryContents();
    UE_LOG(LogTemp, Warning, TEXT("InventoryPanel::RefreshInventory - NumItems: %d"), Contents.Num());

    InventoryWrapBox->ClearChildren();

    for (UVMEquipment* const& InventoryItem : Contents)
    {
        UE_LOG(LogTemp, Warning, TEXT("  Slot for item: %s"),
            InventoryItem ? *InventoryItem->GetEquipmentInfo().ItemName : TEXT("NULL ITEM"));

        UVMInventoryItemSlot* ItemSlot =
            CreateWidget<UVMInventoryItemSlot>(this, InventorySlotClass);

        ItemSlot->OnItemDoubleClicked.AddDynamic(this, &UVMInventoryPanel::HandleItemDoubleClicked);

        ItemSlot->SetItemReference(InventoryItem);  // 여기서 SetItemReference 로그가 떠야 함

        InventoryWrapBox->AddChildToWrapBox(ItemSlot);
    }

    SetInfoText();
}

void UVMInventoryPanel::HandleItemDoubleClicked(UVMEquipment* Item)
{
    /*UE_LOG(LogTemp, Warning, TEXT("InventoryPanel::HandleItemDoubleClicked: %s"),
        Item ? *Item->GetEquipmentInfo().ItemName : TEXT("NULL"));

    if (!Item || !InventoryReference)
        return;

    // 인벤토리의 Owner는 보통 캐릭터일 것
    AActor* Owner = InventoryReference->GetOwner();
    class AVMCharacterHeroBase* Hero = Cast<AVMCharacterHeroBase>(Owner);
    if (!Hero)
        return;

    Hero->EquipFromInventory(Item);*/

    UE_LOG(LogTemp, Warning, TEXT("InventoryPanel::HandleItemDoubleClicked: %s"),
        Item ? *Item->GetEquipmentInfo().ItemName : TEXT("NULL"));

    if (!Item || !InventoryReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: Item or InventoryReference is NULL"));
        return;
    }

    AVMCharacterHeroBase* Hero = Cast<AVMCharacterHeroBase>(InventoryReference->GetOwner());
    if (!Hero)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: Hero cast failed"));
        return;
    }

    // 1) 스탯 적용
    Hero->EquipFromInventory(Item);

    int32 EquippedSlotIndex = INDEX_NONE;

    if (APlayerController* PC = Cast<APlayerController>(Hero->GetController()))
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: PlayerController OK"));

        if (AVMCharacterHeroHUD* HUD = PC->GetHUD<AVMCharacterHeroHUD>())
        {
            UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: HUD OK"));

            if (HUD->EquipmentPanel)
            {
                UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: EquipmentPanel is valid, calling TryEquipToEmptySlot"));

                EquippedSlotIndex = HUD->EquipmentPanel->TryEquipToEmptySlot(Item);

                UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: TryEquipToEmptySlot returned %d"), EquippedSlotIndex);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: EquipmentPanel is NULL"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: GetHUD cast failed"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: PlayerController cast failed"));
    }

    // 2) 성공했으면 인벤토리에서 제거
    if (EquippedSlotIndex != INDEX_NONE)
    {
        InventoryReference->RemoveItem(Item);
        RefreshInventory();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryPanel: No free equipment slot, item stays in inventory"));
    }
}

void UVMInventoryPanel::SetInfoText() const
{
}

bool UVMInventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

}

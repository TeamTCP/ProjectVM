// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hero/VMCharacterHeroBase.h"
#include "UI/Inventory/VMInventoryItemSlot.h"
#include "VMEquipmentPanel.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTVM_API UVMEquipmentPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    void RefreshEquipment(AVMCharacterHeroBase* Hero);

protected:
    // 무기칸 슬롯 (재사용 가능)
    UPROPERTY(meta = (BindWidget))
    UVMInventoryItemSlot* WeaponSlot;
    virtual void NativeConstruct() override;

    // 인벤토리에서 더블클릭하면 여기로 던져줄 함수
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    int32 TryEquipToEmptySlot(UVMEquipment* Item);

protected:
    // WBP 안의 6개 슬롯 바인딩
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot0;
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot1;
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot2;
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot3;
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot4;
    UPROPERTY(meta = (BindWidget)) 
    TObjectPtr<UVMInventoryItemSlot> Weapon_Slot5;

    // 코드에서 다루기 쉽게 배열로 묶어두기
    UPROPERTY()
    TArray<TObjectPtr<UVMInventoryItemSlot>> SlotWidgets;

    // 각 슬롯에 실제 어떤 아이템이 들어있는지
    UPROPERTY()
    TArray<TObjectPtr<UVMEquipment>> EquippedItems;

};

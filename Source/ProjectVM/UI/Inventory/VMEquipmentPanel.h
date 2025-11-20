// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Hero/VMCharacterHeroBase.h"
#include "VMEquipmentPanel.generated.h"


class UUniformGridPanel;
class UVMEquipment;
class UVMEquipmentInfo;
class UVMEquipmentItemSlot;
class UVMInventoryItemSlot;


/**
 * 
 */
UCLASS()
class PROJECTVM_API UVMEquipmentPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    // 인벤토리에서 더블클릭하면 여기로 던져줄 함수
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    int32 TryEquipToEmptySlot(UVMEquipment* Item);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
    UUniformGridPanel* SlotGrid;

    // 코드에서 다루기 쉽게 배열로 묶어두기
    UPROPERTY()
    TArray<TObjectPtr<UVMInventoryItemSlot>> WeaponSlots;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UVMEquipmentItemSlot> SlotClass;

    UPROPERTY(VisibleAnywhere, Category = "Equipment Slot")
    TObjectPtr<UVMEquipment> ItemReference;

    //UPROPERTY()
    //UVMEquipmentItemSlot* Slot;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UVMEquipment* GetItem() const { return ItemReference; }

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ClearItem();
 
    void RefreshFromItem();


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

   
    // 각 슬롯에 실제 어떤 아이템이 들어있는지
    UPROPERTY()
    TArray<TObjectPtr<UVMEquipment>> EquippedItems;

};

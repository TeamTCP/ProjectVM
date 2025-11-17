// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/VMShopListViewEntry.h"
#include "UI/Shop/VMShopItemDataObject.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Materials/MaterialInterface.h" 
#include "Materials/MaterialInstanceDynamic.h"  
#include "Components/ListView.h"

#define LOG_POS(Format, ...) \
    UE_LOG(LogTemp, Log, TEXT("%s(%d): " Format), \
    ANSI_TO_TCHAR(__FILE__), __LINE__, ##__VA_ARGS__)

void UVMShopListViewEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	ShopItemDataObject = Cast<UVMShopItemDataObject>(ListItemObject);

	if (ShopItemDataObject == nullptr)
	{
		return;
	}

	if (ShopItemDataObject->EquipmentInfo == nullptr)
	{
		LOG_POS("아직 초기화 안됨");
		return;
	}

	if (ItemNameText != nullptr)
	{
		ItemNameText->SetText(FText::FromString(ShopItemDataObject->EquipmentInfo->ItemName));

	}

	if (ItemImage)
	{
		UMaterialInterface* BaseMat = Cast<UMaterialInterface>(ItemImage->GetBrush().GetResourceObject());
		if (BaseMat)
		{
			// Dynamic Material이면 Parent를 원본 Material로 변경
			if (UMaterialInstanceDynamic* DynMat = Cast<UMaterialInstanceDynamic>(BaseMat))
			{
				BaseMat = DynMat->GetBaseMaterial(); // 원본 Material로 가져오기
			}

			ItemMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, GetTransientPackage());
			ItemImage->SetBrushFromMaterial(ItemMaterialInstance);
		}
	}

	if (ItemMaterialInstance)
	{
		ItemMaterialInstance->SetScalarParameterValue(TEXT("ColumnIndex"), ShopItemDataObject->EquipmentInfo->AtlasCol);
		ItemMaterialInstance->SetScalarParameterValue(TEXT("RowIndex"), ShopItemDataObject->EquipmentInfo->AtlasRow);
	}

	//아이템 변경사항 구독
	ShopItemDataObject->OnItemCountUpdated.AddUObject(this, &UVMShopListViewEntry::ChangeItemCount);

	ChangeItemCount();
}

void UVMShopListViewEntry::NativeConstruct()
{
	if (ItemButton != nullptr)
	{
		ItemButton->OnClicked.AddDynamic(this, &UVMShopListViewEntry::OnListButtonClicked);
	}
}

void UVMShopListViewEntry::ChangeItemCount()
{
	if (ShopItemDataObject->CurrentCount <= 0)
	{
		UListView* List = Cast<UListView>(GetOwningListView());
		if (List)
		{
			List->RemoveItem(ShopItemDataObject);
		}
	}

	if (ItemCountText != nullptr)
	{
		ItemCountText->SetText(FText::AsNumber(ShopItemDataObject->CurrentCount));
	}
	if (ItemAllPriceText != nullptr)
	{
		int NowMoney = ShopItemDataObject->CurrentCount * ShopItemDataObject->EquipmentInfo->ItemLevel * 2000;
		ItemAllPriceText->SetText(FText::AsNumber(NowMoney));
	}
}

void UVMShopListViewEntry::OnListButtonClicked()
{
	if (ShopItemDataObject == nullptr)
	{	
		LOG_POS("ShopItemDataObject is nullptr");
		return;
	}
	ShopItemDataObject->ChangeItemCount(false);
}
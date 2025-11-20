// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/VMInventoryItemSlot.h"
#include "UI/Inventory/VMInventoryTooltip.h"
#include "UI/Inventory/VMDragItemVisual.h"
#include "Inventory/VMItemDragDropOperation.h"

#include "Item/Equipment/VMEquipmentInfo.h"
#include "Item/Equipment/VMEquipment.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"




void UVMInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (TooltipClass)
	{
		UVMInventoryTooltip* ToolTip = CreateWidget<UVMInventoryTooltip>(this, TooltipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}
}

void UVMInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	const FVMEquipmentInfo& Info = ItemReference->GetEquipmentInfo();
	/*if (ItemReference)
	{
		ItemBorder->SetBrushColor(FLinearColor::Gray);
	}

	ItemIcon->SetBrushFromTexture(Info.Icon);

	if (!ItemReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryItemSlot: ItemReference is null in NativeConstruct"));
		return;
	}


	ItemBorder->SetBrushColor(FLinearColor::Gray);

	if (Info.Icon)
	{
		ItemIcon->SetBrushFromTexture(Info.Icon);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryItemSlot: Icon is null for item %s"),
			*Info.ItemName);
	}
	*/

	if (ItemBorder)
	{
		ItemBorder->SetBrushColor(FLinearColor::Transparent);
	}

}

FReply UVMInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Slot::OnMouseButtonDown"));

	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return Reply.Unhandled();
}

void UVMInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UVMInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (!ItemReference)
		return;

	const FVMEquipmentInfo& Info = ItemReference->GetEquipmentInfo();

	if (DragItemVisualClass)
	{
		UVMDragItemVisual* DragVisual =
			CreateWidget<UVMDragItemVisual>(this, DragItemVisualClass);

		if (Info.Icon)
		{
			DragVisual->ItemIcon->SetBrushFromTexture(Info.Icon);
		}
		DragVisual->ItemBorder->SetBrushColor(ItemBorder->GetBrushColor());

		UVMItemDragDropOperation* DragItemOperation =
			NewObject<UVMItemDragDropOperation>();

		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;
		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;

		UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected: drag op created for %s"),
			*Info.ItemName);

	}
}

void UVMInventoryItemSlot::SetItemReference(UVMEquipment* ItemIn)
{ 
	ItemReference = ItemIn;

	UE_LOG(LogTemp, Warning,
		TEXT("InventorySlot(%s in %s)::SetItemReference Item=%s"),
		*GetName(),
		*GetOuter()->GetName(),
		ItemReference ? *ItemReference->GetEquipmentInfo().ItemName : TEXT("NULL"));

	RefreshFromItem();   // 여기서만 처리
};


void UVMInventoryItemSlot::SetUp(const FVMEquipmentInfo& Info)
{
	//// 다이나믹 머터리얼 생성
	//if (ItemIcon && ItemIcon->GetBrush().GetResourceObject())
	//{
	//	UMaterialInterface* BaseMat = Cast<UMaterialInterface>(ItemIcon->GetBrush().GetResourceObject());
	//	if (BaseMat != nullptr)
	//	{
	//		ItemMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, this);
	//		ItemIcon->SetBrushFromMaterial(ItemMaterialInstance);
	//	}
	//}
	////머터리얼 파라미터 설정
	//if (ItemMaterialInstance)
	//{
	//	ItemMaterialInstance->SetScalarParameterValue(TEXT("ColumnIndex"), Info.AtlasCol);
	//	ItemMaterialInstance->SetScalarParameterValue(TEXT("RowIndex"), Info.AtlasRow);
	//}

		// 1) 아직 MID가 없다면 한 번만 생성
	if (!ItemMaterialInstance)
	{
		UMaterialInterface* BaseMat = nullptr;

		// Atlas 머터리얼 변수가 따로 있다면 우선 사용
		if (AtlasMaterial)
		{
			BaseMat = AtlasMaterial;
		}
		else if (ItemIcon)
		{
			// 초기 Brush에 물려 있는 M_ItemAtlas (또는 MI_ItemAtlas)를 한 번만 사용
			BaseMat = Cast<UMaterialInterface>(ItemIcon->GetBrush().GetResourceObject());
		}

		if (BaseMat)
		{
			ItemMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, this);
			ItemIcon->SetBrushFromMaterial(ItemMaterialInstance);

			UE_LOG(LogTemp, Warning,
				TEXT("InventorySlot(%s)::SetUp created MID from %s"),
				*GetName(), *BaseMat->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning,
				TEXT("InventorySlot(%s)::SetUp: BaseMat is NULL"),
				*GetName());
		}
	}

	// 2) 이미 MID가 있으면, 파라미터만 갱신
	if (ItemMaterialInstance)
	{
		ItemMaterialInstance->SetScalarParameterValue(TEXT("ColumnIndex"), Info.AtlasCol);
		ItemMaterialInstance->SetScalarParameterValue(TEXT("RowIndex"), Info.AtlasRow);

		UE_LOG(LogTemp, Warning,
			TEXT("InventorySlot(%s)::SetUp set Col=%d Row=%d"),
			*GetName(), Info.AtlasCol, Info.AtlasRow);
	}

}

void UVMInventoryItemSlot::RefreshFromItem()
{
	
	//UE_LOG(LogTemp, Warning,
	//	TEXT("InventorySlot(%s in %s)::RefreshFromItem ENTER, Ref=%s, IconWidget=%s"),
	//	*GetName(),
	//	*GetOuter()->GetName(),
	//	ItemReference ? *ItemReference->GetEquipmentInfo().ItemName : TEXT("NULL"),
	//	*GetNameSafe(ItemIcon));

	//if (!ItemIcon || !ItemBorder)
	//	return;

	//if (!ItemReference)
	//{
	//	// 브러시(Atlas 머터리얼)는 그대로 둔 채로 숨기기만
	//	ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	//	ItemBorder->SetBrushColor(FLinearColor::White);
	//	return;
	//}

	//const FVMEquipmentInfo& Info = ItemReference->GetEquipmentInfo();

	//if (Info.Icon)
	//{
	//	ItemIcon->SetBrushFromTexture(Info.Icon);
	//}
	UE_LOG(LogTemp, Warning,
		TEXT("InventorySlot(%s in %s)::RefreshFromItem ENTER, Ref=%s"),
		*GetName(),
		*GetOuter()->GetName(),
		ItemReference ? *ItemReference->GetEquipmentInfo().ItemName : TEXT("NULL"));

	if (!ItemIcon || !ItemBorder)
		return;

	// 아이템 없으면 숨기기
	if (!ItemReference)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// ★ 여기에서 다시 보여주기
	ItemIcon->SetVisibility(ESlateVisibility::Visible);
	ItemBorder->SetBrushColor(FLinearColor::White); // 원하는 색

	const FVMEquipmentInfo& Info = ItemReference->GetEquipmentInfo();

	// 아이콘 세팅 방식(Atlas or Icon 텍스처)은 인벤토리에서 이미 잘 나오는 그대로 유지
	/*if (Info.Icon)
	{
		ItemIcon->SetBrushFromTexture(Info.Icon);
	}*/
	SetUp(Info);
}




bool UVMInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply UVMInventoryItemSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("InventorySlot::OnMouseButtonDoubleClick"));

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && ItemReference)
	{
		// 더블클릭 시 장착 요청 브로드캐스트
		OnItemDoubleClicked.Broadcast(ItemReference);
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

void UVMInventoryItemSlot::ClearItem()
{
	ItemReference = nullptr;

	if (ItemIcon)
	{
		ItemIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	if (ItemBorder)
	{
		ItemBorder->SetBrushColor(FLinearColor::White);
	}
}
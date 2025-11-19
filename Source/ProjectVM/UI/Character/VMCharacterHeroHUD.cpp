// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Character/VMCharacterHeroHUD.h"
#include "UI/Inventory/VMInteractionWidget.h"
#include "UI/Inventory/VMMainMenu.h"
#include "UI/Inventory/VMInventoryPanel.h"
#include "UI/Inventory/VMEquipmentPanel.h"

AVMCharacterHeroHUD::AVMCharacterHeroHUD()
{

}

void AVMCharacterHeroHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();

	UE_LOG(LogTemp, Warning, TEXT("HeroHUD::BeginPlay called"));
	UE_LOG(LogTemp, Warning, TEXT("HeroHUD: InventoryPanelClass = %s, EquipmentPanelClass = %s"),
		InventoryPanelClass ? *InventoryPanelClass->GetName() : TEXT("NULL"),
		EquipmentPanelClass ? *EquipmentPanelClass->GetName() : TEXT("NULL"));

	UE_LOG(LogTemp, Log, TEXT("QWER MainMenuClass 확인 전"));
	if (MainMenuClass)
	{
		UE_LOG(LogTemp, Log, TEXT("QWER MainMenuClass HIHI"));
		MainMenuWidget = CreateWidget<UVMMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UVMInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	// 인벤토리 패널
	if (InventoryPanelClass && PC)
	{
		InventoryPanel = CreateWidget<UVMInventoryPanel>(PC, InventoryPanelClass);
		if (InventoryPanel)
		{
			UE_LOG(LogTemp, Warning, TEXT("HeroHUD: InventoryPanel created: %s"), *InventoryPanel->GetName());
			InventoryPanel->AddToViewport(0);
			InventoryPanel->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	// 장비 패널
	if (EquipmentPanelClass && PC)
	{
		EquipmentPanel = CreateWidget<UVMEquipmentPanel>(PC, EquipmentPanelClass);
		if (EquipmentPanel)
		{
			UE_LOG(LogTemp, Warning, TEXT("HeroHUD: EquipmentPanel created: %s"), *EquipmentPanel->GetName());
			EquipmentPanel->AddToViewport(0);
			EquipmentPanel->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HeroHUD: EquipmentPanelClass is NULL or PC is NULL"));
	}
}


void AVMCharacterHeroHUD::DisplayMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[DisplayMenu] MainMenuWidget is nullptr"));
	}

}

void AVMCharacterHeroHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[HideMenu] MainMenuWidget is nullptr"));
	}
}


void AVMCharacterHeroHUD::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		UE_LOG(LogTemp, Display, TEXT("[ToggleMenu] is true"));
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("[ToggleMenu] is false"));
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AVMCharacterHeroHUD::ShowInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AVMCharacterHeroHUD::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AVMCharacterHeroHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}
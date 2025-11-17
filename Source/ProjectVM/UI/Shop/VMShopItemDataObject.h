
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item/Equipment/VMEquipmentInfo.h"
#include "Shop/VMEntryParentInterface.h"
#include "VMShopItemDataObject.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnItemCountUpdated);
UCLASS()
class PROJECTVM_API UVMShopItemDataObject : public UObject
{
	GENERATED_BODY()

public:
	//아이템 카운트 변경. 변경 성공 여부 bool 반환
	bool ChangeItemCount(bool bIsAdd)
	{
		//아이템 추가
		if (bIsAdd)
		{
			//한 번에 살 수 있는 아이템 수 99개로 제한
			if (CurrentCount >= 99)
			{
				return false;
			}
			++CurrentCount;

		}
		//아이템 삭제
		else
		{
			--CurrentCount;
			ParentInterface->RemoveListItem(EquipmentInfo->ItemLevel * (-2000), this);
		}
		OnItemCountUpdated.Broadcast(); //위젯에 변경 사항 알림.
		return true;
	}

public:
	FOnItemCountUpdated OnItemCountUpdated;

	const FVMEquipmentInfo* EquipmentInfo;

	UPROPERTY()
	int32 CurrentCount = 1;

	IVMEntryParentInterface* ParentInterface; // ListEntry -> Screen 호출용 인터페이스

	TArray<int32> InventoryIndexes; //Inventory의 index. 삭제시 내림차순 정렬 후 사용. 
};

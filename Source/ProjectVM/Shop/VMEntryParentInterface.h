#pragma once

#include "UObject/Interface.h"
#include "VMEntryParentInterface.generated.h"

class UVMShopItemDataObject;

//ListView의 아이템 추가, 제거 등으로 총 아이템 가격이 바뀔 때 UI에 적용시키기 위한 인터페이스
UINTERFACE(MinimalAPI)
class UVMEntryParentInterface : public UInterface
{
    GENERATED_BODY()
};

class IVMEntryParentInterface
{
    GENERATED_BODY()

public:
    virtual void RemoveListItem(int32 Price, UVMShopItemDataObject *ListObject) = 0; // Screen이 구현하게 되는 함수
};
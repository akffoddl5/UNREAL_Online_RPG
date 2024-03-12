// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "InventoryComponent.h"

UItemBase::UItemBase(): BaseItemQuantity(0), BaseItemType(), BaseItemAssetData(), OwningInventory(nullptr)
{
}

UItemBase* UItemBase::CreateCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->BaseItemID = this->BaseItemID;
	ItemCopy->BaseItemType = this->BaseItemType;
	ItemCopy->BaseItemQuantity = this->BaseItemQuantity;
	ItemCopy->BaseItemTextData = this->BaseItemTextData;
	ItemCopy->BaseItemNumericData = this->BaseItemNumericData;
	ItemCopy->BaseItemStatistics = this->BaseItemStatistics;
	ItemCopy->BaseItemAssetData = this->BaseItemAssetData;
	ItemCopy->bIsCopy = true;
	
	return ItemCopy;
}

// 아이템 수량이 변경됐을 때 사용함
void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != BaseItemQuantity)
	{
		BaseItemQuantity = FMath::Clamp(NewQuantity,0,
			BaseItemNumericData.bIsStackable? BaseItemNumericData.MaxStackSize:1);

		if (OwningInventory)
		{
			if (BaseItemQuantity <= 0)
			{
				OwningInventory->RemoveSingleItem(this);
			}
		}
	}
}

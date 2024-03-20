// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterIdle.generated.h"

/**
 * 
 */
UCLASS()
class ONLINE_RPG_API UBTTaskMonsterIdle : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTaskMonsterIdle();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	float RandomFloatInRange(float Min, float Max);
};

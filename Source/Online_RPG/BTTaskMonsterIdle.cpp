// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskMonsterIdle.h"
#include "EnemyDog.h"
#include "AIController.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterIdle::UBTTaskMonsterIdle()
{
	NodeName = "Idle";
}

EBTNodeResult::Type UBTTaskMonsterIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() != nullptr)
	{
		AEnemyDog* QQ = Cast<AEnemyDog>(OwnerComp.GetAIOwner()->GetPawn());

		FVector tmp = OwnerComp.GetBlackboardComponent()->GetValueAsVector("SpawnLocation");
		tmp.X += RandomFloatInRange(-5, 5);
		tmp.Y += RandomFloatInRange(-5, 5);
		tmp.Z += RandomFloatInRange(-1, 1);

		if (QQ->CanMoveToPosition(tmp))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("SpawnLocation", tmp);
		}

	}

	return EBTNodeResult::Succeeded;
}
float UBTTaskMonsterIdle::RandomFloatInRange(float Min, float Max)
{
	return FMath::FRandRange(Min, Max);
}
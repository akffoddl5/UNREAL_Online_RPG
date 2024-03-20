// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "EnemyDog.h"
#include "CMSpawnManager.generated.h"

UCLASS()
class ONLINE_RPG_API ACMSpawnManager : public AActor
{
    GENERATED_BODY()

public:
    ACMSpawnManager();

    void SpawnEnemyDog(FVector Location, float Delay);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AEnemyDog> EnemyDogClass;

};

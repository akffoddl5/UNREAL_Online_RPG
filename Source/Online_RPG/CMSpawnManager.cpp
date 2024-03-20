// Fill out y
//our copyright notice in the Description page of Project Settings.
#include "CMSpawnManager.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "EnemyDog.h"
// Sets default values

ACMSpawnManager::ACMSpawnManager()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
}

void ACMSpawnManager::BeginPlay()
{

}

void ACMSpawnManager::SpawnEnemyDog(FVector Location, float Delay)
{
    if (HasAuthority()) 
    {
<<<<<<< HEAD
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, Location]()
            {
                AEnemyDog* SpawnedEnemyDog = GetWorld()->SpawnActor<AEnemyDog>(EnemyDogClass, Location, FRotator::ZeroRotator);
                if (SpawnedEnemyDog)
                {
                    // Additional setup for the spawned enemy dog can be done here.
                }
            }), Delay, false);
=======
        ////UE_LOG(LogTemp, Error, TEXT("Actor is null!"));
        return;
>>>>>>> main
    }
    
}


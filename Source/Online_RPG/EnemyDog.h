// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyProjectile.h"
#include "EnemyDog.generated.h"

UCLASS()
class ONLINE_RPG_API AEnemyDog : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyDog();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void OnDeath();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Attack();

	void Idle();

	bool CanMoveToPosition(FVector TargetLocation);

protected:
	// Called when the game starts or when spawned

public:	

	// Called to bind functionality to input
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool RangeCheck();

private:
	UPROPERTY(VisibleAnywhere, Category = "VALUE")
	FVector SpawnLocation;
	UPROPERTY(VisibleAnywhere, Category = "VALUE")
	FRotator SpawnRotation;
	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float Damage1 = 1.f;
	UPROPERTY(VisibleAnywhere)
	bool IsDead = false;
	

	UPROPERTY(EditAnywhere)
	class UParticleSystem *Attack1Particle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> AttackProjectile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyDog> EnemySelf;
	void SpawnSelf();
	FTimerHandle TimerHandle_MyFunction;

	UPROPERTY(EditAnywhere)
	float AttackRange = 500;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float RespawnTime = 5.0f;

	void Die();

	void SpawnDebugSphere(FVector Location, float Radius);
	void SpawnProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AEnemyDog> EnemyDogClass;
};

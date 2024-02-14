// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyDog.generated.h"

UCLASS()
class ONLINE_RPG_API AEnemyDog : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyDog();
	void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float Damage1 = 1.f;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *Attack1Particle;

	void SpawnDebugSphere(FVector Location, float Radius);

};

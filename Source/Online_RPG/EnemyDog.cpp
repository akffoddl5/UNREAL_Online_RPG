// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDog.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "EnemyProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "CMSpawnManager.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "AI/NavigationSystemBase.h"
// Sets default values
AEnemyDog::AEnemyDog()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	Health = MaxHealth;

}

// Called when the game starts or when spawned
void AEnemyDog::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = this->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Monster Location = %s"), *FString::Printf(TEXT("%f / %f / %f"), this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z));
	Health = MaxHealth;
	RangeCheck();
	//AEnemyAIController* OwnerController = Cast<AEnemyAIController>(this->GetController());


}

// Called every frame
void AEnemyDog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyDog::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyDog::Attack_Implementation()
{
	SpawnProjectile();
}



float AEnemyDog::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	AEnemyAIController* OwnerController = Cast<AEnemyAIController>(this->GetController());
	if(OwnerController)
		OwnerController->SetPlayer(Cast<APawn>(DamageCauser));
	if (IsDead) return ActualDamage;

	if (Health - ActualDamage <= 0)
	{
		OnDeath();
		return ActualDamage;
	}

	Health -= ActualDamage;
	UE_LOG(LogTemp, Display, TEXT("Actor took damage: %f Heath = %f"), ActualDamage, Health);
	return ActualDamage;
}


void AEnemyDog::SpawnDebugSphere(FVector Location, float Radius)
{
	DrawDebugSphere(
		GetWorld(),
		Location,
		Radius,
		20,
		FColor::Red,
		false,
		2, // 스피어를 유지할 시간(초)
		0,
		1
	);
}

void AEnemyDog::SpawnProjectile()
{
	TSubclassOf<AEnemyProjectile> ActorClassToSpawn = AEnemyProjectile::StaticClass();

	FVector ProjectileSpawnLocation = this->GetActorLocation();
	FRotator ProjectileSpawnRotation = this->GetActorRotation();

	AActor* Projectile = GetWorld()->SpawnActor<AEnemyProjectile>(AttackProjectile, ProjectileSpawnLocation, ProjectileSpawnRotation);

}

bool AEnemyDog::RangeCheck()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	float TargetDis = FVector::Dist(this->GetActorLocation(), PlayerPawn->GetActorLocation());

	if (AttackRange >= TargetDis)
	{
		return true;
	}
	return false;

}
void AEnemyDog::OnDeath()
{
	if (IsDead) return;
	FVector NewSpawnLocation = SpawnLocation + FVector(100, 0, 0);
	//ACMSpawnManager::GetInstance()->RespawnActor(SpawnLocation, 5.0f);

	Health = 0;
	IsDead = true;
	FRotator MyRotator(0.0f, 0.0f, 190.0f);
	this->AddActorLocalRotation(MyRotator);
	AEnemyAIController* OwnerController = Cast<AEnemyAIController>(this->GetController());
	if (OwnerController)
	{
		OwnerController->Dead();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEnemyAIController Is Nullptr"));
	}
	ACMSpawnManager* SpawnManager = Cast<ACMSpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACMSpawnManager::StaticClass()));
	if (SpawnManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action Spawn"));

		SpawnManager->SpawnEnemyDog(GetActorLocation(), RespawnTime);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Spawn Error"));

	}
	Destroy();
	
}

void AEnemyDog::Idle()
{

}
bool AEnemyDog::CanMoveToPosition(FVector TargetLocation)
{
	// 네비게이션 시스템을 가져옵니다.
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys) return false;

	// 네비게이션 데이터를 가져옵니다.
	const ANavigationData* NavData = NavSys->GetDefaultNavDataInstance();

	// 네비게이션 쿼리 필터를 생성합니다.
	FSharedConstNavQueryFilter QueryFilter = UNavigationQueryFilter::GetQueryFilter(*NavData, this, UNavigationQueryFilter::StaticClass());

	// 경로를 찾습니다.
	FPathFindingQuery Query(this, *NavData, GetActorLocation(), TargetLocation, QueryFilter);
	FPathFindingResult Result = NavSys->FindPathSync(Query);

	// 결과의 성공 여부와 경로의 유효성을 검증합니다.
	UE_LOG(LogTemp, Warning, TEXT("CanMoveToPosition:Result.IsSuccessful() =  %s /  Result.Path.IsValid() =  %s  / !Result.Path->GetPathPoints().IsEmpty() = %s"), Result.IsSuccessful(), Result.Path.IsValid(), !Result.Path->GetPathPoints().IsEmpty());

	return Result.IsSuccessful() && Result.Path.IsValid() && !Result.Path->GetPathPoints().IsEmpty();
}


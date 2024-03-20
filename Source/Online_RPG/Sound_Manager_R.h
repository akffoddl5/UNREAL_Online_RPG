// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound_Manager_R.generated.h"

enum class SOUND_TYPE : uint8;

UCLASS()
class ONLINE_RPG_API ASound_Manager_R : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASound_Manager_R();

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
	int32 Ground_Check(APawn* MyPawn);

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* BackgroundMusicComponent;

	//이펙트 오디오 갯수
	int32 SoundEffect_NUM =5;
	
	UPROPERTY(VisibleAnywhere, Category = "Audio")
	TArray<UAudioComponent*> SoundEffectComponents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Manager_Init();
	void Sound_Play(SOUND_TYPE Sound_Type, int32 Audio_idx, FVector Location, FRotator Rotator, APawn* MyPawn);
	
	UPROPERTY()
	TMap<SOUND_TYPE, USoundBase*> Sound_Map;
	//=============에셋매니저로 수동 로드 SOUND=============== 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Ingame_Sound_queue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Walk_Sound_queue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Walk_Sound_Water_queue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Walk_Sound_Grass_queue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Boss_BGM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Shoot_Sound_queue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Fire_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AsyncLoadSound")
	USoundBase* Explosion_Sound;
	
	
	//=====================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Login_Sound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Btn_Click_Sound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Btn_Fail_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Btn_Game_Start;


	//잔디 스태틱메시
	UPROPERTY(EditAnywhere)
	UStaticMesh* Grass_Flower;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Grass_1;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* Grass_2;
	
	
};



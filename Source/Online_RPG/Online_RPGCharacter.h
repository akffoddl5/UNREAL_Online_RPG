// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Online_RPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOnline_RPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AOnline_RPGCharacter();

	/** 프로퍼티 리플리케이션 */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** 최대 체력 게터*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** 현재 체력 게터*/
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** 현재 체력 세터. 값을 0과 MaxHealth 사이로 범위제한하고 OnHealthUpdate를 호출합니다. 서버에서만 호출되어야 합니다.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float healthValue);

	/** 대미지를 받는 이벤트. APawn에서 오버라이드됩니다.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	/** �봽濡쒗띁�떚 由ы뵆由ъ���씠�뀡 */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


	/** 플레이어의 최대 체력. 체력의 최댓값입니다. 이 값은 스폰 시 시작되는 캐릭터의 체력 값입니다.*/
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	/** 플레이어의 현재 체력. 0이 되면 죽은 것으로 간주됩니다.*/
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	/** 현재 체력에 가해진 변경에 대한 RepNotify*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** 업데이트되는 체력에 반응. 서버에서는 수정 즉시 호출, 클라이언트에서는 RepNotify에 반응하여 호출*/
	void OnHealthUpdate();


	UPROPERTY(EditDefaultsOnly, Category = "Gameplay|Projectile")
	TSubclassOf<class AProjectile_dm> ProjectileClass;

	/** 발사 딜레이, 단위는 초. 테스트 발사체의 발사 속도를 제어하는 데 사용되지만, 서버 함수의 추가분이 SpawnProjectile을 입력에 직접 바인딩하지 않게 하는 역할도 합니다.*/
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float FireRate;

	/** true인 경우 발사체를 발사하는 프로세스 도중입니다. */
	bool bIsFiringWeapon;

	/** 무기 발사 시작 함수*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartFire();

	/** 무기 발사 종료 함수. 호출되면 플레이어가 StartFire를 다시 사용할 수 있습니다.*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();

	/** 발사체를 스폰하는 서버 함수*/
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** 스폰 사이에 발사 속도 딜레이를 넣는 타이머 핸들*/
	FTimerHandle FiringTimer;
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** �뵆�젅�씠�뼱�쓽 理쒕�� 泥대젰. 泥대젰�쓽 理쒕뙎媛믪엯�땲�떎. �씠 媛믪�� �뒪�룿 �떆 �떆�옉�릺�뒗 罹먮┃�꽣�쓽 泥대젰 媛믪엯�땲�떎.*/
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;

	/** �뵆�젅�씠�뼱�쓽 �쁽�옱 泥대젰. 0�씠 �릺硫� 二쎌�� 寃껋쑝濡� 媛꾩＜�맗�땲�떎.*/
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float Mana;

	/** �쁽�옱 泥대젰�뿉 媛��빐吏� 蹂�寃쎌뿉 ����븳 RepNotify*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	/** �뾽�뜲�씠�듃�릺�뒗 泥대젰�뿉 諛섏쓳. �꽌踰꾩뿉�꽌�뒗 �닔�젙 利됱떆 �샇異�, �겢�씪�씠�뼵�듃�뿉�꽌�뒗 RepNotify�뿉 諛섏쓳�븯�뿬 �샇異�*/
	UFUNCTION()
	void OnHealthUpdate();

	UPROPERTY(EditDefaultsOnly, Category="Gameplay|Projectile")
	TSubclassOf<class ARED_Projectile> ProjectileClass;

	/** 諛쒖궗 �뵜�젅�씠, �떒�쐞�뒗 珥�. �뀒�뒪�듃 諛쒖궗泥댁쓽 諛쒖궗 �냽�룄瑜� �젣�뼱�븯�뒗 �뜲 �궗�슜�릺吏�留�, �꽌踰� �븿�닔�쓽 異붽��遺꾩씠 SpawnProjectile�쓣 �엯�젰�뿉 吏곸젒 諛붿씤�뵫�븯吏� �븡寃� �븯�뒗 �뿭�븷�룄 �빀�땲�떎.*/
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;

	/** true�씤 寃쎌슦 諛쒖궗泥대�� 諛쒖궗�븯�뒗 �봽濡쒖꽭�뒪 �룄以묒엯�땲�떎. */
	bool bIsFiringWeapon;

	/** 臾닿린 諛쒖궗 �떆�옉 �븿�닔*/
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void StartFire();

	/** 臾닿린 諛쒖궗 醫낅즺 �븿�닔. �샇異쒕릺硫� �뵆�젅�씠�뼱媛� StartFire瑜� �떎�떆 �궗�슜�븷 �닔 �엳�뒿�땲�떎.*/
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StopFire();

	/** 諛쒖궗泥대�� �뒪�룿�븯�뒗 �꽌踰� �븿�닔*/
	UFUNCTION(Server, Reliable)
	void HandleFire();

	/** �뒪�룿 �궗�씠�뿉 諛쒖궗 �냽�룄 �뵜�젅�씠瑜� �꽔�뒗 ����씠癒� �빖�뱾*/
	FTimerHandle FiringTimer;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** 理쒕�� 泥대젰 寃뚰꽣*/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** �쁽�옱 泥대젰 寃뚰꽣*/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** �쁽�옱 泥대젰 �꽭�꽣. 媛믪쓣 0怨� MaxHealth �궗�씠濡� 踰붿쐞�젣�븳�븯怨� OnHealthUpdate瑜� �샇異쒗빀�땲�떎. �꽌踰꾩뿉�꽌留� �샇異쒕릺�뼱�빞 �빀�땲�떎.*/
	UFUNCTION(BlueprintCallable, Category="Health")
	void SetCurrentHealth(float healthValue);

	/** ���誘몄��瑜� 諛쏅뒗 �씠踰ㅽ듃. APawn�뿉�꽌 �삤踰꾨씪�씠�뱶�맗�땲�떎.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	float TakeDamage( float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser ) override;
};



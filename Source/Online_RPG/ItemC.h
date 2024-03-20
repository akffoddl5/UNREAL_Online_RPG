// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemC.generated.h"

class UInventoryComponent;
class IItemInteractionInterface;
class AInventoryHUD;

USTRUCT()
struct FInteractingData
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* CurrentInteracting;

	FInteractingData():CurrentInteracting(nullptr){}
	
};

UCLASS()
class ONLINE_RPG_API AItemC : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AItemC();
	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory;}
	
	UPROPERTY()
	AInventoryHUD* HUD;

	UPROPERTY(VisibleAnywhere,Category = "Character | Interaction")
	TScriptInterface<IItemInteractionInterface> InteractionTarget;
	
	float InteractionDistance = 300.0f;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	UInventoryComponent* PlayerInventory;
	
	FInteractingData InteractionData;
	void FoundNoInteract();
	void FoundInteract(AActor* NewInteract);
	void BeginInteract();
	void Interact();
	void EndInteract();
	void OpenInventory();
	void UpdateInteractionWidget() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CheckInteraction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};

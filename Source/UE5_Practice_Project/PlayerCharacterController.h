// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterController.generated.h"

UCLASS()
class UE5_PRACTICE_PROJECT_API APlayerCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterController();

	// Camera that follows the player model
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameSceneCamera")
	UCameraComponent* CameraComponent;

	// Box component for alligning the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerAlignmentTool")
	UBoxComponent* BoxComponent;

	// Handle to manage the cooldown for the attack input
	FTimerHandle AttackCoolDownHandle;

	// animation asset for the attack animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimationAsset* AttackAnimationAsset;

	// animation asset for the run animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimationAsset* RunAnimationAsset;

	// bool check for if the player attacked or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	bool bIsAttacking;

	// float for how long the timer needs to be
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variables")
	float AttackCoolDownTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	
	UFUNCTION()
	void ResetAttackCoolDown();

};
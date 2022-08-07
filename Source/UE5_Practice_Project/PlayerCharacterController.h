// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterController.generated.h"

UCLASS()
class UE5_PRACTICE_PROJECT_API APlayerCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();
	void AttackCoolDown(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UAnimationAsset* AttackAnimationAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UAnimationAsset* RunAnimationAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables")
	float timer;
};

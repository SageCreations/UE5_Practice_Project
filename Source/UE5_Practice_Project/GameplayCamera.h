// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"
#include "GameplayCamera.generated.h"

UCLASS()
class UE5_PRACTICE_PROJECT_API AGameplayCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameplayCamera();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly)
	UArrowComponent* ArrowComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

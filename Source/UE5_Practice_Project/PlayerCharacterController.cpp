// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include <string>

// Sets default values
APlayerCharacterController::APlayerCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	bIsAttacking = false;
	timer = 0.0f;
}

// Called every frame
void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAttacking == true && timer > 0.0f)
	{
		timer -= 1.1f * DeltaTime; 
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, std::to_string(timer).data());
		if (timer < 0.0f)
		{
			bIsAttacking = false;
			this->GetMesh()->PlayAnimation(RunAnimationAsset, true);
		}
	}
	

}

// Called to bind functionality to input
void APlayerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Attack",IE_Pressed, this, &APlayerCharacterController::Attack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

void APlayerCharacterController::Attack()
{
	if (bIsAttacking == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("attack button pressed"));

		timer = AttackAnimationAsset->GetPlayLength();
		this->GetMesh()->PlayAnimation(AttackAnimationAsset, false);
		bIsAttacking = true;
	}
}


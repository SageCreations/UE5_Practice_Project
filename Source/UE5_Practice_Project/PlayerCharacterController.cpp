#include "PlayerCharacterController.h"
#include <string>

#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	// makes the character move to the right on the x-axis by force.
	this->APawn::AddMovementInput(this->GetActorForwardVector(), 1.0f, true);
	
	AttackCoolDown(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Button input for attack binds ('LMB' or 'E')
	PlayerInputComponent->BindAction("Attack",IE_Pressed, this, &APlayerCharacterController::Attack);
	// Button input for jump binds ('RMB' or 'spacebar') ((not sure if StopJump() func is needed or not))
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

//function activates when attack key bind is pressed.
void APlayerCharacterController::Attack()
{
	// the action only works if the timer code reaches below zero resetting the bool to false.
	if (bIsAttacking == false)
	{
		// debug message for when button input was accepted
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("attack button pressed"));

		timer = AttackAnimationAsset->GetPlayLength();
		this->GetMesh()->PlayAnimation(AttackAnimationAsset, false);
		bIsAttacking = true;
	}
}

void APlayerCharacterController::AttackCoolDown(float DeltaTime)
{
	// This is the current code for timing cooldown on player's attack speed
	// TODO: figure out a way to time it based off the attack swing animation time length.
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


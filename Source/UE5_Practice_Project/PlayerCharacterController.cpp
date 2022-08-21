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
	AttackCoolDownTimer = AttackAnimationAsset->GetPlayLength();
}

// Called every frame
void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// makes the character move to the right on the x-axis by force.
	this->APawn::AddMovementInput(this->GetActorForwardVector(), 1.0f, true);
	
	
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

		// Starts a timer for the attack cooldown
		GetWorldTimerManager().SetTimer(AttackCoolDownHandle, this, &APlayerCharacterController::ResetAttackCoolDown, AttackCoolDownTimer, false);
		
		this->GetMesh()->PlayAnimation(AttackAnimationAsset, false);
		
		bIsAttacking = true;
	}
}


// Sets the attack boolean back to false and changes the animation back to running
void APlayerCharacterController::ResetAttackCoolDown()
{
	this->GetMesh()->PlayAnimation(RunAnimationAsset, true);
	bIsAttacking = false;
}


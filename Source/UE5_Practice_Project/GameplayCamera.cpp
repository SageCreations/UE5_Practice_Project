// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCamera.h"

// Sets default values
AGameplayCamera::AGameplayCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ForwardDirection");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("GameSceneCamera");
	RootComponent = ArrowComponent;
	CameraComponent->SetupAttachment(RootComponent);
	

	

}

// Called when the game starts or when spawned
void AGameplayCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameplayCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// makes the character move to the right on the x-axis by force.
	this->APawn::AddMovementInput(FVector(this->GetActorForwardVector()), 1.0f,  true);
}

// Called to bind functionality to input
void AGameplayCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


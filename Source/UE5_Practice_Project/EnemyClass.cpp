// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyClass.h"

// Sets default values
AEnemyClass::AEnemyClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyClass::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(15.0f);
}

// Called every frame
void AEnemyClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


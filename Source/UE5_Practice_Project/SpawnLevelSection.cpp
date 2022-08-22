// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevelSection.h"
#include "PlayerCharacterController.h"
#include <string>
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"

// Sets default values
ASpawnLevelSection::ASpawnLevelSection() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creating the components
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Starter Floor");
	BoxTriggerPoint = CreateDefaultSubobject<UBoxComponent>("Trigger Next Spawn");
	BoxSpawnPoint = CreateDefaultSubobject<UBoxComponent>("New Floor Spawn Point");

	

	// Creating the hierarchy
	RootComponent = StaticMeshComponent;
	BoxTriggerPoint->SetupAttachment(StaticMeshComponent);
	BoxSpawnPoint->SetupAttachment(StaticMeshComponent);

	// Setting Generate overlap events
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	BoxSpawnPoint->SetGenerateOverlapEvents(false);
	BoxTriggerPoint->SetGenerateOverlapEvents(true);
	

}

// Called when the game starts or when spawned
void ASpawnLevelSection::BeginPlay()
{
	Super::BeginPlay();
	// Create a overlap begin trigger for the BoxTriggerPoint component
	BoxTriggerPoint->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevelSection::OnBeginOverlap);

	// sets the object's life for 5 seconds (calls destroy() at end of timer) - (this is a feature built in Actor parent class)
	SetLifeSpan(LifeSpanTimer);

	
	
	
	
}

// Called every frame
void ASpawnLevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASpawnLevelSection::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Not sure if this first if statement is needed, check at later date.
	if(this->BoxTriggerPoint == OverlappedComponent)
	{
		// checks for OtherActor being the PlayerCharacterController Class
		if (Cast<APlayerCharacterController>(OtherActor))
		{
			// if its true then spawn the next floor piece
			AddNextSection();
		}
	}
}

// Adds a new Floor Tile Blueprint in the world
void ASpawnLevelSection::AddNextSection()
{
	SpawnFloor();

	//TODO: redesign how the spawning works, make it more abstract so that each object spawned is blueprint with its own code.

	// spawns the rest of the stuff that will be placed on the floor
	SpawnEnemies();
	SpawnObjects();
}

// Spawns next floor peice
void ASpawnLevelSection::SpawnFloor()
{
	// Get a random int32
	int RandNum = FMath::RandRange(0, FloorList.Max());
	
	// Spawn actor of desired class
	GetWorld()->SpawnActor<AActor>(
		FloorList[RandNum],
		BoxSpawnPoint->GetComponentTransform().GetLocation() + FloorSpawnOffset.GetLocation(),
		BoxSpawnPoint->GetComponentTransform().Rotator()
	);
}

// Spawns an enemy
void ASpawnLevelSection::SpawnEnemies()
{
	// Get a random int32
	int RandNum = FMath::RandRange(0, 1);
	
	//Sets the location range for the enemy (absolute world loc, idk why)
	FVector Location = FVector(FMath::FRandRange(MinEnemySpawnRange, MaxEnemySpawnRange), 0.0f, EnemyHeightPosition);
	
	//Spawn the enemy relative to the boxSpawnPoint 
	GetWorld()->SpawnActor<AActor>(
		EnemyList[RandNum], 
		BoxSpawnPoint->GetComponentTransform().GetLocation() + Location,
		BoxSpawnPoint->GetComponentTransform().Rotator()
	);

}

void ASpawnLevelSection::SpawnObjects()
{

}






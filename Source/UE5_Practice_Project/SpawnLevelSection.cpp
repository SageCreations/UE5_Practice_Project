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
			AddFloorTile();
		}
	}
}

// Adds a new Floor Tile Blueprint in the world
void ASpawnLevelSection::AddFloorTile()
{
	UWorld* World = GetWorld();
	const FActorSpawnParameters Params;

	// Spawn actor of desired class
	AActor* SpawnedSection = World->SpawnActor<ASpawnLevelSection>(
		this->GetClass(),
		BoxSpawnPoint->GetComponentTransform().GetLocation() + FloorSpawnOffset.GetLocation(),
		BoxSpawnPoint->GetComponentTransform().Rotator(),
		Params
	);

	// spawns the rest of the stuff that will be placed on the floor
	SpawnEnemies();
	SpawnObjects();
}

void ASpawnLevelSection::SpawnEnemies()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("entered function"));
	UWorld* World = GetWorld();
	// create params struct
	const FActorSpawnParameters Params;

	// get random enemy from the list
	int RandNum = FMath::TruncToInt(FMath::FRandRange(0, 2));
	
	// get random location betwenn range variables
	FVector location = FVector(0.0f, 0.0f, 20.0f);
		//FVector(FMath::FRandRange(MinEnemySpawnRange.X, MaxEnemySpawnRange.X), 0.0f, 50.0f);

	// TODO: for somereason this doesnt error but it doesnt spawn either, figure it out.
	AActor* SpawnedEnemy = World->SpawnActor<AActor>(
		EnemyList[RandNum]->GetClass(),
		location,
		BoxSpawnPoint->GetComponentTransform().Rotator(),
		Params
	);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("should have spawned the enemy"));
}

void ASpawnLevelSection::SpawnObjects()
{

}






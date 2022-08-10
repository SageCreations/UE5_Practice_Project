// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevelSection.h"

// Sets default values
ASpawnLevelSection::ASpawnLevelSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Starter Floor");
	BoxSpawnPoint = CreateDefaultSubobject<UBoxComponent>("Next Spawn Point");
	BoxTriggerPoint = CreateDefaultSubobject<UBoxComponent>("Trigger Next Spawn");

	RootComponent = StaticMeshComponent;
	BoxSpawnPoint->SetupAttachment(RootComponent);
	BoxTriggerPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpawnLevelSection::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASpawnLevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FTransform ASpawnLevelSection::GetAttachTransform() const
{
	return BoxSpawnPoint->GetComponentTransform();
}


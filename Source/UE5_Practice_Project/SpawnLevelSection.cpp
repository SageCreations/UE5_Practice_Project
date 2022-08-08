// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevelSection.h"

#include "Engine/TextureCube.h"

// Sets default values
ASpawnLevelSection::ASpawnLevelSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Starter Floor");
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("Next Spawn Point");
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Trigger Next Spawn");

	RootComponent = ArrowComponent;
	StaticMeshComponent->SetupAttachment(RootComponent);
	BoxComponent->SetupAttachment(RootComponent);
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


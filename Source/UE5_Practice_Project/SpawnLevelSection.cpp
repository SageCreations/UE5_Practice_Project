// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevelSection.h"

#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"


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

	bSpawn = false;
	SpawnNextSection();
}

// Called every frame
void ASpawnLevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnLevelSection::SpawnNextSection()
{
	/*
	https://cpp.hotexamples.com/examples/-/UWorld/SpawnActor/cpp-uworld-spawnactor-method-examples.html
	File: ChildActorComponent.cpp Project: xiangyuan/Unreal4

		void UChildActorComponent::CreateChildActor()
{
    // Kill spawned actor if we have one
    DestroyChildActor();

    // This is no longer needed
    if (CachedInstanceData)
    {
        delete CachedInstanceData;
        CachedInstanceData = nullptr;
    }

    // If we have a class to spawn.
    if(ChildActorClass != nullptr)
    {
        UWorld* World = GetWorld();
        if(World != nullptr)
        {
            // Before we spawn let's try and prevent cyclic disaster
            bool bSpawn = true;
            AActor* Actor = GetOwner();
            while (Actor && bSpawn)
            {
                if (Actor->GetClass() == ChildActorClass)
                {
                    bSpawn = false;
                    UE_LOG(LogChildActorComponent, Error, TEXT("Found cycle in child actor component '%s'.  Not spawning Actor of class '%s' to break."), *GetPathName(), *ChildActorClass->GetName());
                }
                Actor = Actor->ParentComponentActor.Get();
            }

            if (bSpawn)
            {
                FActorSpawnParameters Params;
                Params.bNoCollisionFail = true;
                Params.bDeferConstruction = true; // We defer construction so that we set ParentComponentActor prior to component registration so they appear selected
                Params.bAllowDuringConstructionScript = true;
                Params.OverrideLevel = GetOwner()->GetLevel();
                Params.Name = ChildActorName;
                if (!HasAllFlags(RF_Transactional))
                {
                    Params.ObjectFlags &= ~RF_Transactional;
                }

                // Spawn actor of desired class
                FVector Location = GetComponentLocation();
                FRotator Rotation = GetComponentRotation();
                ChildActor = World->SpawnActor(ChildActorClass, &Location, &Rotation, Params);

                // If spawn was successful,
                if(ChildActor != nullptr)
                {
                    ChildActorName = ChildActor->GetFName();

                    // Remember which actor spawned it (for selection in editor etc)
                    ChildActor->ParentComponentActor = GetOwner();

                    ChildActor->AttachRootComponentTo(this);

                    // Parts that we deferred from SpawnActor
                    ChildActor->FinishSpawning(ComponentToWorld);
                }
            }
        }
    }
}
	**/


	if(bSpawn)
	{
		
	}

	//UWorld::SpawnActor(BoxSpawnPoint->GetRelativeLocation(), BoxSpawnPoint->GetRelativeRotation(), );
}


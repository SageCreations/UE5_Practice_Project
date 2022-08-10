// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE5_Practice_ProjectGameModeBase.h"

// Called when the game starts or when spawned
void AUE5_Practice_ProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 2; i++)
	{
		ASpawnLevelSection* OBJ_SPL = nullptr;
		//replace with parameter with OBJ_SPL when done testing
		AddFloorTile(TestSpawnFunc);
	}
}

void AUE5_Practice_ProjectGameModeBase::AddFloorTile(UBlueprint* OBJSpawnLevelSection)
{
	if(OBJSpawnLevelSection != nullptr)
	{
		if(UWorld* World = GetWorld(); World != nullptr)
		{
			// Before we spawn let's try and prevent cyclic disaster
			bool bSpawn = true;
			const AActor* Actor = GetOwner();
			while (Actor && bSpawn)
			{
				if (Actor->GetClass() == OBJSpawnLevelSection->GetClass())
				{
					bSpawn = false;
					//UE_LOG(LogChildActorComponent, Error, TEXT("Found cycle in child actor component '%s'.  Not spawning Actor of class '%s' to break."), *GetPathName(), *ChildActorClass->GetName());
				}
				Actor = Actor->GetParentActor();
			}

			if (bSpawn)
			{
				// make a SpawnParameters struct
				FActorSpawnParameters Params;
				Params.bNoFail = true;
				Params.bDeferConstruction = true; // We defer construction so that we set ParentComponentActor prior to component registration so they appear selected
				Params.bAllowDuringConstructionScript = true;
				Params.OverrideLevel = GetOwner()->GetLevel();
				Params.Name = "SpawnedSection";
				if (!HasAllFlags(RF_Transactional))
				{
					Params.ObjectFlags &= ~RF_Transactional;
				}
				
				// Spawn actor of desired class
				//NextSpawnPoint = OBJSpawnLevelSection->GetAttachTransform();
				AActor* SpawnedSection = nullptr;
				SpawnedSection = World->SpawnActor<ASpawnLevelSection> (
					OBJSpawnLevelSection->GetClass(),
					NextSpawnPoint.GetLocation(),
					NextSpawnPoint.Rotator(),
					Params
				);
				
				// If spawn was successful,
				if(SpawnedSection != nullptr)
				{
					Params.Name = SpawnedSection->GetFName();

					// Remember which actor spawned it (for selection in editor etc)
					SpawnedSection->SetRootComponent(Actor->GetRootComponent());
					

					// Parts that we deferred from SpawnActor
					SpawnedSection->FinishSpawning(NextSpawnPoint);
				}
			}
		}
	}
}



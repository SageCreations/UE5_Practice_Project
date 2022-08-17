// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevelSection.h"

#include "PlayerCharacterController.h"
#include "Engine/Engine.h"

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

	BoxTriggerPoint->SetGenerateOverlapEvents(true);
	

}

// Called when the game starts or when spawned
void ASpawnLevelSection::BeginPlay()
{
	Super::BeginPlay();
	BoxTriggerPoint->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevelSection::OnBoxTriggerOverlap);
	
	
}

// Called every frame
void ASpawnLevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Gets the Transform of the BoxSpawnPoint Component
FTransform ASpawnLevelSection::GetAttachTransform() const
{
	return BoxSpawnPoint->GetComponentTransform();
}

// WTF IS GOING ON!!!!!!!!!!!!!!!!!!!!!
void ASpawnLevelSection::OnBoxTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Something Overlapped"));

	if (OtherActor == Cast<APlayerCharacterController>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Character is the one Overlapping"));
		//TODO: Call the next section of the floor here.
		//AddFloorTile(this);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("chara not overlapping"));
	}
}

// TODO: doesn't work, recreate it from scratch.
void ASpawnLevelSection::AddFloorTile(const ASpawnLevelSection* OBJSpawnLevelSection) const
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
				static_cast<UE::Math::TTransform<double>>(NextSpawnPoint) = OBJSpawnLevelSection->GetAttachTransform();
				AActor* SpawnedSection = World->SpawnActor<ASpawnLevelSection> (
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




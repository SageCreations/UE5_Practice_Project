// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnLevelSection.generated.h"

UCLASS()
class UE5_PRACTICE_PROJECT_API ASpawnLevelSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnLevelSection();
	
	// Mesh for the floor (temp asset, replace with type UBlueprint)
	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

	// Box Component used for the next floor's spawn point
	UPROPERTY(EditAnywhere, Category="Components")
	UBoxComponent* BoxSpawnPoint;

	// Box Component used detecting the player overlapping it to trigger the spawn
	UPROPERTY(EditAnywhere, Category="Components")
	UBoxComponent* BoxTriggerPoint;

	// An array of enemy blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UBlueprint*> EnemyList;

	// An array of floor blueprints (static mesh is temp, only for testing)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UStaticMesh*> FloorList;

	// An array of object blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UBlueprint*> ObjectList;

	// only use the x range and set the most left side you want the enemy to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	FVector MinEnemySpawnRange;

	// only use the x range and set the most right side you want the enemy to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	FVector MaxEnemySpawnRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	FTransform FloorSpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	float LifeSpanTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Used for overlapping on the triggerbox box component
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	// Spawns the next floor piece
	void AddFloorTile();

	// Spawns enemies for the next section
	void SpawnEnemies();

	// Spawns objects for the next section
	void SpawnObjects();
	
	

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemyClass.h"
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

	// An array of enemies
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy Variables")
	TArray<TSubclassOf<AEnemyClass>> EnemyList;

	// An array of floor blueprints (static mesh is temp, only for testing)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Floor Variables")
	TArray<TSubclassOf<AActor>> FloorList;

	// An array of object blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Object Variables")
	TArray<TSubclassOf<AActor>> ObjectList;

	// only use the x range and set the most left side you want the enemy to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables")
	float MinEnemySpawnRange;

	// only use the x range and set the most right side you want the enemy to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables")
	float MaxEnemySpawnRange;

	// used for the range on height (z-axis)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Variables")
	float EnemyHeightPosition;

	// offset needed for the floor spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	FTransform FloorSpawnOffset;

	// Seconds to wait untill self destruct of object
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
	
	// Spawns the next section (calls all the spawn functions)
	void AddNextSection();

	// spawns the floor
	void SpawnFloor();

	// Spawns enemies for the next section
	void SpawnEnemies();

	// Spawns objects for the next section
	void SpawnObjects();
	
	

};

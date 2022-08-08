// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactoryBasicShape.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnLevelSection.generated.h"

UCLASS()
class UE5_PRACTICE_PROJECT_API ASpawnLevelSection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnLevelSection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UBlueprint*> EnemyList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UStaticMesh*> FloorList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AssetsToSpawn")
	TArray<UBlueprint*> ObjectList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnNextSection();

};

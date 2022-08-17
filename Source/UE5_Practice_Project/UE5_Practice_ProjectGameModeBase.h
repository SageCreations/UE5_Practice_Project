// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpawnLevelSection.h"
#include "GameFramework/GameModeBase.h"
#include "UE5_Practice_ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PRACTICE_PROJECT_API AUE5_Practice_ProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
};

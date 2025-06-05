// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SphereSpawner.h"
#include "FlockAgentSettings.h"
#include "FlockBehaviour.h"
#include "FlockSphereSpawner.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API AFlockSphereSpawner : public ASphereSpawner
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Properties")
	UFlockAgentSettings* AgentSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flock|Properties")
	UFlockBehaviour* Behaviour;
	
protected:
	virtual void OnSpawn(AActor* Spawned) override;
};

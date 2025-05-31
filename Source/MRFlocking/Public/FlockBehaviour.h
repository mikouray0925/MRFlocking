// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FlocksContext.h"
#include "FlockAgentContext.h"
#include "FlockBehaviour.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MRFLOCKING_API UFlockBehaviour : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Flocking")
    FVector CalculateVelocity(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext);
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) PURE_VIRTUAL(UFlockBehaviour::CalculateVelocity, return FVector::ZeroVector;);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    virtual void DrawGizmos(UWorld* World, const FVector& Location, float Radius = 100.f)
    {
        if (!World) return;

        DrawDebugSphere(World, Location, Radius, 12, FColor::Green, false, -1.0f, 0, 1.0f);
    }
};

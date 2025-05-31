// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "CompositeBehaviour.generated.h"

USTRUCT(BlueprintType)
struct FBehaviourWeightPair
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    UFlockBehaviour* Behaviour = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    float Weight = 1.0f;
};

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UCompositeBehaviour : public UFlockBehaviour
{
	GENERATED_BODY()
	
public:
    // 在編輯器中可以設定多個行為及其權重
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    TArray<FBehaviourWeightPair> Behaviours;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    bool NoVelocityNoWeight = true;

    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        FVector VelocitySum = FVector::ZeroVector;
        float WeightSum = 0.0f;

        for (const FBehaviourWeightPair& Pair : Behaviours)
        {
            if (!Pair.Behaviour) continue;

            FVector Velocity = Pair.Behaviour->CalculateVelocity(DeltaTime, FlocksContext, AgentContext);

            if (!Velocity.IsNearlyZero() || !NoVelocityNoWeight)
            {
                VelocitySum += Velocity * Pair.Weight;
                WeightSum += Pair.Weight;
            }
        }

        if (WeightSum > 0)
        {
            return VelocitySum / WeightSum;
        }
        else
        {
            return FVector::ZeroVector;
        }
    }

    virtual void DrawGizmos(UWorld* World, const FVector& Location, float Radius = 100.f) override
    {
        for (const FBehaviourWeightPair& Pair : Behaviours)
        {
            if (Pair.Behaviour)
            {
                Pair.Behaviour->DrawGizmos(World, Location, Radius);
            }
        }
    }
};

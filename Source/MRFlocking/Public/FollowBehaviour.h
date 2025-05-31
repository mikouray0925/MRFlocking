// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "FollowBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UFollowBehaviour : public UFlockBehaviour
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Follow")
    int32 TargetIndex = 0;

    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        if (FlocksContext.TargetPoints.IsValidIndex(TargetIndex))
        {
            const FVector& TargetLocation = FlocksContext.TargetPoints[TargetIndex]->GetActorLocation();
            return (TargetLocation - AgentContext.Position).GetSafeNormal() * AgentContext.BaseSpeed;
        }
        else
        {
            return FVector::ZeroVector;
        }
    }
};

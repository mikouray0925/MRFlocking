// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "CohesionBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UCohesionBehaviour : public UFlockBehaviour
{
    GENERATED_BODY()

public:
    // 可在編輯器中設定，或直接使用 AgentSettings->DetectionChannels
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    TArray<TEnumAsByte<ECollisionChannel>> DetectionChannels;

    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        const TArray<UPrimitiveComponent*>& NearbyColliders = AgentContext.NearbyColliders;
        const int32 NearbyCount = NearbyColliders.Num();

        if (NearbyCount <= 0)
        {
            return AgentContext.Position;
        }

        FVector MeanPosition = AgentContext.Position;
        int32 ValidCount = 1;

        for (UPrimitiveComponent* Collider : NearbyColliders)
        {
            if (!Collider) continue;

            const ECollisionChannel Channel = Collider->GetCollisionObjectType();
            if (DetectionChannels.Contains(Channel))
            {
                MeanPosition += Collider->GetComponentLocation();
                ++ValidCount;
            }
        }

        if (ValidCount > 0)
        {
            MeanPosition /= ValidCount;
        }

        return (MeanPosition - AgentContext.Position + AgentContext.Forward) * AgentContext.BaseSpeed;
    }
	
};

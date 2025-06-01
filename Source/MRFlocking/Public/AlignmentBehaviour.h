// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "AlignmentBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UAlignmentBehaviour : public UFlockBehaviour
{
	GENERATED_BODY()

public:
    /** 可在 Editor 設定的偵測頻道 (相當於 Unity 的 LayerMask) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    TArray<TEnumAsByte<ECollisionChannel>> DetectionChannels;

    /** 計算速度向量 */
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        if (AgentContext.NearbyColliders.Num() <= 0)
        {
            return AgentContext.Forward;
        }

        // 計算附近 agent 的平均方向
        FVector MeanDirection = FVector::ZeroVector;
        int NearbyCount = 0;

        for (UPrimitiveComponent* Collider : AgentContext.NearbyColliders)
        {
            if (Collider && DetectionChannels.Contains(Collider->GetCollisionObjectType()))
            {
                FTransform OtherTransform = Collider->GetOwner()->GetTransform();
                MeanDirection += OtherTransform.GetRotation().GetForwardVector();
                ++NearbyCount;
            }
        }

        if (NearbyCount > 0)
        {
            MeanDirection /= NearbyCount;
        }

        return (MeanDirection + AgentContext.Forward) * AgentContext.BaseSpeed;
    }
};

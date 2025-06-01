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
    /** �i�b Editor �]�w�������W�D (�۷�� Unity �� LayerMask) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    TArray<TEnumAsByte<ECollisionChannel>> DetectionChannels;

    /** �p��t�צV�q */
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        if (AgentContext.NearbyColliders.Num() <= 0)
        {
            return AgentContext.Forward;
        }

        // �p����� agent ��������V
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

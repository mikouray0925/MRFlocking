// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "AvoidanceBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UAvoidanceBehaviour : public UFlockBehaviour
{
    GENERATED_BODY()

public:
    /** �����I�������W�D�]�۷�� Unity �� LayerMask�^ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    TArray<TEnumAsByte<ECollisionChannel>> DetectionChannels;

    /** �����b�| */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
    float AvoidanceRadius = 300.f; // Unreal ���O cm�A�o���q�{ 3m

    /** �p��t�צV�q */
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
    {
        // �����b�|���o�W�L�����b�|
        if (AvoidanceRadius > AgentContext.DetectionRadius)
        {
            UE_LOG(LogTemp, Warning, TEXT("Avoidance radius %.2f is greater than detection radius %.2f. Clamping to detection radius."),
                AvoidanceRadius, AgentContext.DetectionRadius);
            AvoidanceRadius = AgentContext.DetectionRadius;
        }

        float SquareAvoidanceRadius = AvoidanceRadius * AvoidanceRadius;

        // �p��������V
        int AvoidanceCount = 0;
        FVector AvoidanceDirection = FVector::ZeroVector;

        for (UPrimitiveComponent* Collider : AgentContext.NearbyColliders)
        {
            if (!Collider || !DetectionChannels.Contains(Collider->GetCollisionObjectType()))
            {
                continue;
            }

            FVector Direction = AgentContext.Position - Collider->GetComponentLocation();
            float SquareDist = Direction.SizeSquared();

            if (SquareDist < SquareAvoidanceRadius)
            {
                AvoidanceCount++;
                AvoidanceDirection += Direction.GetSafeNormal() / SquareDist;
            }
        }

        if (AvoidanceCount <= 0)
        {
            return AgentContext.Forward * AgentContext.BaseSpeed;
        }
        else
        {
            AvoidanceDirection /= AvoidanceCount;
        }

        return (AvoidanceDirection + AgentContext.Forward) * AgentContext.BaseSpeed;
    }
	
};

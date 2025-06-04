// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "SphereShape.h"
#include "BoxShape.h"
#include "ConfinedBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class MRFLOCKING_API UConfinedBehaviour : public UFlockBehaviour
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
	float Power = 2.0f;

	virtual FVector CalculateVelocity_Implementation(float DeltaTime, const FlocksContext& FlocksContext, const FlockAgentContext& AgentContext) override
	{
		// 根據 FlocksContext.Confiner 的類型執行對應計算
		if (const ASphereShape* SphereConfiner = Cast<ASphereShape>(FlocksContext.Confiner))
		{
			FVector ToCenter = SphereConfiner->GetActorLocation() - AgentContext.Position;
			float DistanceUnits = ToCenter.Size() / SphereConfiner->Radius;
			return ToCenter * AgentContext.BaseSpeed * FMath::Pow(DistanceUnits, Power);
		}
        else if (const ABoxShape* Box = Cast<ABoxShape>(FlocksContext.Confiner))
        {
            const FVector ToCenter = Box->GetActorLocation() - AgentContext.Position;

            const FVector Right = FlocksContext.ConfinerRight;
            const FVector Up = FlocksContext.ConfinerUp;
            const FVector Forward = FlocksContext.ConfinerForward;

            const FVector RightPortion = FVector::DotProduct(ToCenter, Right) * Right;
            const FVector UpPortion = FVector::DotProduct(ToCenter, Up) * Up;
            const FVector ForwardPortion = FVector::DotProduct(ToCenter, Forward) * Forward;

            const FVector HalfSize = Box->GetWorldSize() * 0.5f;

            const float RightUnits = RightPortion.Size() / FMath::Max(HalfSize.X, KINDA_SMALL_NUMBER);
            const float UpUnits = UpPortion.Size() / FMath::Max(HalfSize.Y, KINDA_SMALL_NUMBER);
            const float ForwardUnits = ForwardPortion.Size() / FMath::Max(HalfSize.Z, KINDA_SMALL_NUMBER);

            return AgentContext.BaseSpeed * (
                RightPortion * FMath::Pow(RightUnits, Power) +
                UpPortion * FMath::Pow(UpUnits, Power) +
                ForwardPortion * FMath::Pow(ForwardUnits, Power)
                );
        }

		return FVector::ZeroVector;
	}
};

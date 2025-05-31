// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockBehaviour.h"
#include "SphereShape.h"
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

		// TODO: 以後可以實現 BoxShape 的情況

		return FVector::ZeroVector;
	}
};

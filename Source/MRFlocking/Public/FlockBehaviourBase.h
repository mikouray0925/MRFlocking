// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
// #include "FlockBehaviourBase.generated.h"
#include "FlocksContext.h"  // �A�� FlocksContext ���c
#include "FlockAgentContext.h"  // �A�� FlockAgentContext ���c

/**
 * 
 */
// UCLASS(Abstract, Blueprintable, EditInlineNew)
template<typename TFlocksContext, typename TAgentContext>
class MRFLOCKING_API UFlockBehaviourBase: public UObject
{
	// GENERATED_BODY()
	
public:
    // �µ����禡�A�l��������{
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Flocking")
    FVector CalculateVelocity(float DeltaTime, const TFlocksContext& FlocksContext, const TAgentContext& AgentContext);
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const TFlocksContext& FlocksContext, const TAgentContext& AgentContext) PURE_VIRTUAL(UFlockBehaviourBase::CalculateVelocity, return FVector::ZeroVector;);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
// #include "FlockBehaviourBase.generated.h"
#include "FlocksContext.h"  // 你的 FlocksContext 結構
#include "FlockAgentContext.h"  // 你的 FlockAgentContext 結構

/**
 * 
 */
// UCLASS(Abstract, Blueprintable, EditInlineNew)
template<typename TFlocksContext, typename TAgentContext>
class MRFLOCKING_API UFlockBehaviourBase: public UObject
{
	// GENERATED_BODY()
	
public:
    // 純虛擬函式，子類必須實現
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Flocking")
    FVector CalculateVelocity(float DeltaTime, const TFlocksContext& FlocksContext, const TAgentContext& AgentContext);
    virtual FVector CalculateVelocity_Implementation(float DeltaTime, const TFlocksContext& FlocksContext, const TAgentContext& AgentContext) PURE_VIRTUAL(UFlockBehaviourBase::CalculateVelocity, return FVector::ZeroVector;);
};

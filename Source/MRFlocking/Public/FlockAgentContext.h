// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlockAgentContext.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MRFLOCKING_API FlockAgentContext
{
public:
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector Position;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector Forward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector Up;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    TWeakObjectPtr<AActor> Transform; // ¹ïÀ³ Unity ªº Transform

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    float DetectionRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    float BaseSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector LastVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    FVector LastDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    TArray<UPrimitiveComponent*> NearbyColliders;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    int32 NearbyCollidersCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocks")
    bool bDebugLog;
};
